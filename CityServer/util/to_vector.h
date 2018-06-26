#pragma once

#include <vector>
#include <sstream>

namespace util {

    template<typename T>
    std::vector<T> toVector(const std::string& line) {
        std::vector<T> result;
        std::stringstream ss(line);

        T element;
        while (ss >> element) {
            result.push_back(element);
        }

        return result;
    }

}
