#include "net_settings.h"

using namespace net;
using namespace util;

void net::initializeFromXml(const XmlTree& xmlTree, NetSettings& netSettings) {
    readValueFromXml(netSettings.ipAddress,         xmlTree, "IP.<xmlattr>.value");
    readValueFromXml(netSettings.port,              xmlTree, "Port.<xmlattr>.value");
    readValueFromXml(netSettings.pingImitationMin,  xmlTree, "Ping.<xmlattr>.min");
    readValueFromXml(netSettings.pingImitationMax,  xmlTree, "Ping.<xmlattr>.max");
    readValueFromXml(netSettings.showClients,       xmlTree, "ShowClients.<xmlattr>.flag");
}
