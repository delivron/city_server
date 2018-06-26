#pragma once

#include <cstdint>

#include "query_description.h"

namespace net {

    class NetHandlerInterface {
    public:
        virtual uint32_t                    handle(const QueryDescription& query) = 0;
    };

}
