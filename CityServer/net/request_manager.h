#pragma once

#include "net_types.h"
#include "data_buffer.h"

#include "../util/singleton.h"

namespace net {

    class RequestManager : public util::Singleton<RequestManager> {
    public:
        friend class util::Singleton<RequestManager>;

        bool                            send(const TcpSocketPtr& socket, const DataBufferPtr& data) const;
        bool                            receive(const TcpSocketPtr& socket, const DataBufferPtr& data) const;
    };
    
}
