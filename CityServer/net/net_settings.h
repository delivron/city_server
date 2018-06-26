#pragma once

#include <string>
#include <cstdint>

#include "../util/xml_tree.h"

namespace net {

    struct NetSettings {
        std::string                     ipAddress           = "127.0.0.1";
        uint16_t                        port                = 27000;
        uint16_t                        pingImitationMin    = 0;
        uint16_t                        pingImitationMax    = 0;
        bool                            showClients         = true;
    };

    void                                initializeFromXml(const util::XmlTree& xmlTree, NetSettings& netSettings);

}
