#include "request_manager.h"
#include "header_description.h"

using namespace std;
using namespace net;
using namespace boost::asio;
using namespace boost::asio::ip;

bool RequestManager::send(const TcpSocketPtr& socket, const DataBufferPtr& data) const {
    try {
        socket->write_some(data->getBuffer());
        return true;
    }
    catch (const runtime_error&) {
        return false;
    }
}

bool RequestManager::receive(const TcpSocketPtr& socket, const DataBufferPtr& data) const {
    size_t dataSize = data->getSize();

    if (dataSize == 0) {
        if (socket->available() >= sizeof(HeaderDescription)) {
            data->writeFromSocket(socket, sizeof(HeaderDescription));
        }
        else {
            return false;
        }
    }
    
    HeaderDescription header;
    data->resetReadingPointer();
    data->read(header);

    bool lastBytes = header.getFullSize() > data->getSize();
    bool availableBytes = (socket->available() > 0);

    if (lastBytes && availableBytes) {
        data->writeFromSocket(socket, socket->available());
    }

    return header.getFullSize() <= data->getSize();
}
