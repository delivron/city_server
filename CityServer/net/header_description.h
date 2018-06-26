#pragma once

#include <cstdint>

namespace net
{

    enum class QueryCode : uint8_t {
        HELLO                           = 0,
        GET_DEMO_SCENE                  = 1,
        GET_NEAR_OBJECTS                = 2,
        GET_NEAR_NODES                  = 3,
        GET_NODE_STATIC_OBJECTS         = 4,
        GET_DYNAMIC_OBJECTS             = 5,
    };

    #pragma pack(push, 1)
    struct HeaderDescription {
        uint16_t                        transactionId       = 0;
        uint16_t                        frameNumber         = 1;
        uint16_t                        frameCount          = 1;
        uint32_t                        dataSize            = sizeof(code);
        QueryCode                       code                = QueryCode::HELLO;

        inline size_t                   getFullSize() const noexcept;
    };
    #pragma pack(pop)

    size_t HeaderDescription::getFullSize() const noexcept {
        return sizeof(HeaderDescription) - sizeof(code) + dataSize;
    }

}
