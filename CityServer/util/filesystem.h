#pragma once

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

namespace util {

    std::vector<std::string>            listDirectoryFiles(const boost::filesystem::path& directoryPath, const std::string& format = "");
    std::string                         getFileName(const boost::filesystem::path& filePath);
}
