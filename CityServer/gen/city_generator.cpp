#include "city_generator.h"

#include "../util/filesystem.h"

using namespace std;
using namespace gen;
using namespace obj;
using namespace util;

CityGenerator::CityGenerator(const GeneratorResources& resources) noexcept {
    XmlTree carsXml = readXml(resources.carsDescriptionFile);
    initializeFromXml(carsXml, _carNameToProbability);

    XmlTree roofsXml = readXml(resources.roofsDescriptionFile);
    initializeFromXml(roofsXml, _buildingNameToRoof);

    XmlTree variantsXml = readXml(resources.variantsDescriptionFile);
    initializeFromXml(variantsXml, _nameToVariants);
    
    vector<string> xmlFiles = listDirectoryFiles(resources.areaPresetsDirectory, "xml");
    XmlTreesByPath areaPresetTrees = readXml(xmlFiles);
    initializeFromXml(areaPresetTrees, _areaPresets);
    /*
    initializeFromXml(xmlTree, _objectNameToBoundingBox);
    initializeFromXml(xmlTree, _roofPresets);
    initializeFromXml(xmlTree, _areaPresets);
    */
    
    XmlTree boundingBoxesXml = readXml(resources.boundingBoxesDescriptionFile);
    _gameObjectFactory.initializeBoundingBoxes(boundingBoxesXml);
}

Scene CityGenerator::generate(const CitySettings& settings) const {
    Scene scene;

    return scene;
}

Scene CityGenerator::generateFromXmlFile(const string& xmlFilePath) const {
    Scene scene;

    return scene;
}
