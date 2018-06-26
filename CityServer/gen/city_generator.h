#pragma once

#include "city_settings.h"
#include "generator_types.h"
#include "generator_resources.h"

#include "../obj/scene.h"
#include "../obj/game_object_factory.h"

namespace gen {

    class CityGenerator {
    public:
        CityGenerator(const GeneratorResources& resources) noexcept;

        obj::Scene                      generate(const CitySettings& settings) const;
        obj::Scene                      generateFromXmlFile(const std::string& xmlFilePath) const;

    private:
        obj::GameObjectFactory          _gameObjectFactory;
        ProbabilityByName               _carNameToProbability;
        RoofsByName                     _buildingNameToRoof;
        StringsByName                   _nameToVariants;
        PresetsByName                   _roofPresets;
        PresetsByName                   _areaPresets;
    };

}
