#include <iostream>

#include "obj/scene.h"

#include "net/server.h"
#include "net/net_settings.h"
#include "net/query_handler.h"

#include "gen/city_settings.h"
#include "gen/city_generator.h"

#include "util/xml_tree.h"

using namespace std;
using namespace obj;
using namespace net;
using namespace gen;
using namespace util;

void                initializeSettings(const string& settingsFile, NetSettings& netSettings, CitySettings& citySettings);
GeneratorResources  getGeneratorResources() noexcept;
void                printServerInfo(const NetSettings& netSettings) noexcept;

int main() {
    PrintManager::instance().setParameterWidth(17);

    PrintManager::instance().printTitle("City Server");
    PrintManager::instance().printParameter("IP", "127.0.0.1");
    PrintManager::instance().printParameter("Port", "27000");
    PrintManager::instance().printParameter("Version", "0.9.0");
    cout << endl;

    PrintManager::instance().printTitle("City Information");
    PrintManager::instance().printParameter("Width", "10");
    PrintManager::instance().printParameter("Height", "10");
    PrintManager::instance().printParameter("All objects", "784");
    PrintManager::instance().printParameter("Objects type-0", "149");
    PrintManager::instance().printParameter("Objects type-1", "27");
    PrintManager::instance().printParameter("Objects type-2", "13");
    PrintManager::instance().printParameter("Objects type-3", "157");
    PrintManager::instance().printParameter("Objects type-4", "57");
    PrintManager::instance().printParameter("Objects type-5", "0");
    PrintManager::instance().printParameter("Objects type-6", "206");
    PrintManager::instance().printParameter("Objects type-7", "175");
    PrintManager::instance().printParameter("Ojects in block", "112.00");
    PrintManager::instance().printParameter("Blocks count", "7");
    PrintManager::instance().printParameter("Cars count", "10");
    cout << endl;

    PrintManager::instance().printTitle("Clients Information");
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "|  # |              IP |     data(Kb) | speed(Kb/s) | ping(ms) |  uptime(s) |" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << "|  1 |       127.0.0.1 |        74.93 |        0.00 |       30 |      16.97 |" << endl;
    cout << "|  2 |       127.0.0.1 |        74.93 |        0.00 |       33 |      11.54 |" << endl;
    cout << "|  3 |       127.0.0.1 |        74.93 |        5.26 |        0 |       6.00 |" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << endl;
    system("pause");
    return 0;
    //

    NetSettings netSettings;
    CitySettings citySettings;
    initializeSettings("settings.xml", netSettings, citySettings);

    size_t PARAMETER_NAME_WIDTH = 16;
    PrintManager::instance().setParameterWidth(PARAMETER_NAME_WIDTH);
    printServerInfo(netSettings);
    cout << endl;
    // TODO:
    // дату не показывать
    // big_threes в xml, ошибка!!!

    GeneratorResources resources = getGeneratorResources();
    CityGenerator cityGenerator(resources);
    Scene demoScene = cityGenerator.generate(citySettings);
    Scene cityScene = cityGenerator.generateFromXmlFile("generator_data/demo_scene.xml");
    //print(cityScene);

    QueryHandler queryHandler(demoScene, cityScene);
    Server server(netSettings, queryHandler);
    server.run();
    server.wait();

    return 0;
}

void initializeSettings(const string& settingsFile, NetSettings& netSettings, CitySettings& citySettings) {
    XmlTree serverSettingsXml = readXml(settingsFile);
    
    XmlTree netSettingsXml = serverSettingsXml.get_child("Settings.Net", XmlTree{});
    initializeFromXml(netSettingsXml, netSettings);
    if (netSettings.pingImitationMax < netSettings.pingImitationMin) {
        swap(netSettings.pingImitationMax,netSettings.pingImitationMin);
    }

    XmlTree citySettingsXml = serverSettingsXml.get_child("Settings.City", XmlTree{});
    initializeFromXml(citySettingsXml, citySettings);
}

GeneratorResources getGeneratorResources() noexcept {
    GeneratorResources res;
    res.carsDescriptionFile             = "generator_data/cars.xml";
    res.roofsDescriptionFile            = "generator_data/roofs.xml";
    res.variantsDescriptionFile         = "generator_data/variants_list.xml";
    res.boundingBoxesDescriptionFile    = "generator_data/bounding_boxes.xml";
    res.areaPresetsDirectory            = "generator_data/area_presets";
    res.roofPresetsDirectory            = "generator_data/roof_presets";
    return res;
}

void printServerInfo(const NetSettings& netSettings) noexcept {
    PrintManager::instance().printTitle("City Server");
    PrintManager::instance().printParameter("IP", netSettings.ipAddress);
    PrintManager::instance().printParameter("Port", to_string(netSettings.port));
    PrintManager::instance().printParameter("Version", Server::getFullVersion());
}
