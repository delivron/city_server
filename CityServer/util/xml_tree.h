#pragma once

#include <string>
#include <unordered_map>

#include <boost/property_tree/ptree.hpp>

namespace util {
    
    using XmlTree                       = boost::property_tree::ptree;
    using XmlTreesByPath                = std::unordered_map<std::string, util::XmlTree>;

    XmlTree                             readXml(const std::string& xmlFilePath);
    XmlTreesByPath                      readXml(const std::vector<std::string>& xmlFilesPath);

    template <typename T>
    void readValueFromXml(T& value, const XmlTree& xmlTree, const std::string& path) {
        try {
            value = xmlTree.get<T>(path);
        }
        catch (...) {
        }
    }

}
