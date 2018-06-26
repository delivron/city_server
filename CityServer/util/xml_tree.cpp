#include <boost/property_tree/xml_parser.hpp>

#include "xml_tree.h"

#include "../util/print_manager.h"

using namespace std;
using namespace util;
using namespace boost::property_tree;

XmlTree util::readXml(const string& xmlFilePath) {
    ptree xmlTree;

    try {
        read_xml(xmlFilePath, xmlTree);
    }
    catch (const xml_parser_error&) {
        string errorMessage = "error while opening the file \"" + xmlFilePath + "\"";
        PrintManager::instance().printWarning(errorMessage);
    }

    return xmlTree;
}

XmlTreesByPath util::readXml(const vector<string>& xmlFilesPath) {
    XmlTreesByPath trees;
    for (const string& path : xmlFilesPath) {
        trees[path] = readXml(path);
    }
    return trees;
}
