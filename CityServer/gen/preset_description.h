#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

#include "glm/glm.hpp"

#include "../util/xml_tree.h"

namespace gen {

    struct TransformDescription {
        glm::vec3                       position;
        bool                            isDeafultPositionY  = true;
        std::vector<float>              yAngles             = { 0.0f };
    };

    struct ObjectDescription {
        std::vector<std::string>        modelVariants;
        TransformDescription            transform;
        std::string                     depend;
        bool                            isInverseDepend     = false;
        float                           probability         = 1.0f;
    };

    using ObjectsByName = std::unordered_map<std::string, ObjectDescription>;

    struct PresetDescription {
        uint16_t                        width               = 0;
        uint16_t                        height              = 0;
        ObjectsByName                   objects;
    };

    void                                initializeFromXml(const util::XmlTree& xmlTree, PresetDescription& preset);

}
