#include "filesystem.h"

using namespace std;
using namespace boost::filesystem;

vector<string> util::listDirectoryFiles(const path& directoryPath, const string& format) {
    vector<string> files;
    directory_iterator endIt;
    string formatWithPoint = "." + format;

    for (directory_iterator it(directoryPath); it != endIt; ++it) {
        if (is_regular_file(it->path())) {
            string newFile = it->path().string();
            if (newFile.size() <= formatWithPoint.size()) {
                continue;
            }
            
            string currentFormat = newFile.substr(newFile.size() - formatWithPoint.size());
            if (currentFormat == formatWithPoint) {
                files.push_back(newFile);
            }
        }
    }

    return files;
}

string util::getFileName(const path& filePath) {
    return filePath.stem().string();
}
