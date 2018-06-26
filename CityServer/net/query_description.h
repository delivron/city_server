#pragma once

#include <ctime>

#include "net_types.h"
#include "data_buffer.h"

namespace net {

    struct QueryDescription {
        TcpSocketPtr                    socket;
        DataBufferPtr                   dataBuffer;
        clock_t                         receivedTime        = std::clock();
        clock_t                         handleTime          = std::clock();
    };

}
