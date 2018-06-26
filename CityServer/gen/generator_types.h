#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "preset_description.h"

#include "../util/xml_tree.h"

#include "../obj/bounding_box.h"

namespace gen {

    using ProbabilityByName             = std::unordered_map<std::string, float>;
    using StringsByName                 = std::unordered_map<std::string, std::vector<std::string>>;
    using PresetsByName                 = std::unordered_map<std::string, PresetDescription>;
    using RoofsByName                   = std::unordered_map<std::string, struct RoofDescription>;

    struct RoofDescription {
        std::vector<std::string>        variants;
        float                           yCoordinate;
    };

    void                                initializeFromXml(const util::XmlTree& xmlTree, ProbabilityByName& carProbabilities);
    void                                initializeFromXml(const util::XmlTree& xmlTree, RoofsByName& buldingRoofs);
    void                                initializeFromXml(const util::XmlTree& xmlTree, StringsByName& variants);
    void                                initializeFromXml(const util::XmlTreesByPath& xmlTrees, PresetsByName& presets);

}
