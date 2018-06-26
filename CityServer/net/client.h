#pragma once

#include "net_types.h"
#include "data_buffer.h"

namespace net {

    class Client {
    public:
        Client(const TcpSocketPtr& socket) noexcept;

        TcpSocketPtr                    getSocket() const noexcept;
        DataBufferPtr                   getInputBuffer() const noexcept;

    private:
        const TcpSocketPtr              _socket;
        DataBufferPtr                   _inputBuffer;
    };

}
