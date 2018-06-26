#include "city_settings.h"

using namespace gen;
using namespace util;

void gen::initializeFromXml(const XmlTree& xmlTree, CitySettings& citySettings) {
    readValueFromXml(citySettings.seed,                 xmlTree, "Seed.<xmlattr>.value");
    readValueFromXml(citySettings.width,                xmlTree, "Size.<xmlattr>.width");
    readValueFromXml(citySettings.height,               xmlTree, "Size.<xmlattr>.height");
    readValueFromXml(citySettings.carsCount,            xmlTree, "Cars.<xmlattr>.count");
    readValueFromXml(citySettings.hydrantProbability,   xmlTree, "HydrantProbability.<xmlattr>.value");
    readValueFromXml(citySettings.roofProbability,      xmlTree, "RoofProbability.<xmlattr>.value");
}
