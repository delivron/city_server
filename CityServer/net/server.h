#pragma once

#include <mutex>
#include <thread>
#include <string>
#include <vector>

#include "client.h"
#include "net_types.h"
#include "data_buffer.h"
#include "net_settings.h"
#include "query_handler.h"
#include "query_description.h"
#include "header_description.h"

#include "../util/print_manager.h"

namespace net {

    class Server {
    public:
        Server(const NetSettings& settings, const QueryHandler& handler);
        
        static std::string              getVersion() noexcept;
        static std::string              getFullVersion() noexcept;
        
        bool                            isRunning();
        void                            stop();
        void                            run();
        void                            wait();

    private:
        template <typename Func>
        void                            threadLoop(Func handlerFunc);

        uint16_t                        getRandomPing() const noexcept;
        void                            runThreads();
        void                            handleClients();
        void                            handleQueries();
        void                            handleResponces();
        void                            handleClientsInfo();

        static const std::string        VERSION;

        static IoService                _ioService;

        const NetSettings               _settings;
        QueryHandler                    _handler;
        TcpSocketPtr                    _newClientSocket;
        Acceptor                        _acceptor;
        std::mutex                      _serverMutex;
        std::mutex                      _clientsMutex;
        std::mutex                      _queriesMutex;
        std::thread                     _clientAccepter;
        std::thread                     _queryHandler;
        std::thread                     _responseSender;
        std::thread                     _clientInfoUpdater;
        std::vector<Client>             _clients;
        std::vector<QueryDescription>   _queries;
        bool                            _running;
    };

    template <typename Func>
    void Server::threadLoop(Func handlerFunc) {
        while (isRunning()) {
            try {
                (this->*handlerFunc)();
            }
            catch (...) {
                stop();
                util::PrintManager::instance().printWarning("server failure");
            }
        }
    }

}
