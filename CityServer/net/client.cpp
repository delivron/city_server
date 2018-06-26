#include "client.h"

using namespace std;
using namespace net;

Client::Client(const TcpSocketPtr& socket) noexcept
    : _socket(socket)
{
    _inputBuffer = make_shared<DataBuffer>();
}

TcpSocketPtr Client::getSocket() const noexcept {
    return _socket;
}

DataBufferPtr Client::getInputBuffer() const noexcept {
    return _inputBuffer;
}
