#include <boost/algorithm/string/replace.hpp>

#include "server.h"
#include "server_warnings.h"
#include "request_manager.h"

#include "../util/print_manager.h"

using namespace std;
using namespace net;
using namespace util;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::algorithm;

const string    Server::VERSION = "1.5.0";

IoService       Server::_ioService{};

Server::Server(const NetSettings& settings, const QueryHandler& handler)
    : _settings(settings)
    , _handler(handler)
    , _acceptor(_ioService)
{
    _newClientSocket = make_shared<tcp::socket>(_ioService);
    _running = false;
}

string Server::getVersion() noexcept {
    return VERSION;
}

string Server::getFullVersion() noexcept {
    string fullVersion = VERSION + " (" + string(__DATE__) + ")";
    replace_all(fullVersion, "  ", " ");
    return fullVersion;
}

bool Server::isRunning() {
    bool result;

    _serverMutex.lock();
    result = _running;
    _serverMutex.unlock();

    return result;
}

void Server::stop() {
    _serverMutex.lock();
    _running = false;
    _serverMutex.unlock();
}

void Server::run() {
    if (isRunning()) {
        return;
    }

    tcp::endpoint serverEndPoint;

    try {
        auto addr = address_v4::from_string(_settings.ipAddress);
        serverEndPoint = tcp::endpoint(addr, _settings.port);
    }
    catch (const runtime_error&) {
        string addrAndPort = _settings.ipAddress + ':' + to_string(_settings.port);
        printEndPointWarning(addrAndPort);
    }

    try {
        _acceptor.open(serverEndPoint.protocol());
        _acceptor.set_option(tcp::acceptor::reuse_address(true));
        _acceptor.non_blocking(true);
        _acceptor.bind(serverEndPoint);
        _acceptor.listen();
    }
    catch (const runtime_error& exc) {
        string exceptionDescription = exc.what();
        string methodName = exceptionDescription.substr(0, exceptionDescription.find(':'));
        printRunWarning(methodName);
        return;
    }

    _running = true;
    runThreads();
}

void Server::wait() {
    if (isRunning()) {
        _queryHandler.join();
        _responseSender.join();
        _clientInfoUpdater.join();
        _clientAccepter.join();
    }
}

uint16_t Server::getRandomPing() const noexcept {
    return _settings.pingImitationMin
        + rand() % (_settings.pingImitationMax - _settings.pingImitationMin + 1);
}

void Server::runThreads() {
    if (isRunning()) {
        _clientAccepter = thread([this]() {
            threadLoop(&Server::handleClients);
        });
        _queryHandler = thread([this]() {
            threadLoop(&Server::handleQueries);
        });
        _responseSender = thread([this]() {
            threadLoop(&Server::handleResponces);
        });
        _clientInfoUpdater = thread([this]() {
            threadLoop(&Server::handleClientsInfo);
        });
    }
}

void Server::handleClients() {
    this_thread::sleep_for(1ms);

    boost::system::error_code errorCode;
    _acceptor.accept(*_newClientSocket, errorCode);

    if (errorCode.value() == 0) {
        _clientsMutex.lock();
        _clients.push_back(Client(_newClientSocket));
        _clientsMutex.unlock();

        _newClientSocket = make_shared<tcp::socket>(_ioService);
    }
}

void Server::handleQueries() {
    this_thread::sleep_for(1ms);
    _clientsMutex.lock();

    for (const Client& client : _clients) {
        TcpSocketPtr socket = client.getSocket();
        DataBufferPtr buffer = client.getInputBuffer();

        _queriesMutex.lock();
        auto endIt = end(_queries);
        auto it = find_if(begin(_queries), endIt,
            [socket](const QueryDescription& query) {
                return query.socket == socket;
            }
        );
        _queriesMutex.unlock();

        if (it != endIt) {
            continue;
        }

        bool success = RequestManager::instance().receive(socket, buffer);
        if (success) {
            _queriesMutex.lock();
            _queries.push_back(QueryDescription{ socket, buffer });
            _queries.back().handleTime += static_cast<clock_t>(getRandomPing());
            _queriesMutex.unlock();
        }
    }

    _clientsMutex.unlock();
}

void Server::handleResponces() {
    _queriesMutex.lock();

    if (_queries.size() == 0) {
        _queriesMutex.unlock();
        this_thread::sleep_for(1ms);
        return;
    }

    clock_t currentTime = clock();

    for (size_t i = 0; i < _queries.size(); ++i) {
        QueryDescription& query = _queries[i];

        if (currentTime >= query.handleTime) {
            HeaderDescription header;
            query.dataBuffer->read(header);
            
            uint32_t bytesSended = _handler.handle(query);

            /*
            update cliens info
            clientsMutex.lock();
            clients[queries[i]->socket].addBytes(bytesCount);
            clients[queries[i]->socket].lastPing = currentTime - queries[i]->recivedTime;
            clientsMutex.unlock();
            */

            _queries.erase(_queries.begin() + i);
            --i;
        }
    }

    _queriesMutex.unlock();
}

void Server::handleClientsInfo() {
    this_thread::sleep_for(1ms);
}
