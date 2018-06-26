#pragma once

#include <string>
#include <cstdint>

#include "../util/xml_tree.h"

namespace gen {

    struct CitySettings {
        uint32_t                        seed                = -1;
        uint32_t                        width               = 30;
        uint32_t                        height              = 30;
        uint32_t                        carsCount           = 50;
        float                           hydrantProbability  = 0.3f;
        float                           roofProbability     = 0.5f;
    };

    void                                initializeFromXml(const util::XmlTree& xmlTree, CitySettings& citySettings);

}
