#include <iomanip>
#include <iostream>

#include "print_manager.h"

using namespace std;
using namespace util;

PrintManager::PrintManager() noexcept {
    _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    _typeToColor[ColorType::TITLE]          = Color::YELLOW;
    _typeToColor[ColorType::PARAMETER]      = Color::WHITE;
    _typeToColor[ColorType::INFORMATION]    = Color::LIGHT_GRAY;
    _typeToColor[ColorType::WARNING]        = Color::LIGHT_RED;
    _typeToColor[ColorType::DEFAULT]        = Color::LIGHT_GRAY;

    _parameterWidth = 0;
}

void PrintManager::setColor(ColorType colorType, Color color) noexcept {
    _typeToColor[colorType] = color;
}

void PrintManager::setParameterWidth(size_t width) noexcept {
    _parameterWidth = width;
}

void PrintManager::printTitle(const std::string& title) const noexcept {
    applyColor(_typeToColor.at(ColorType::TITLE));
    cout << "[ " << title << " ]" << endl;
    resetColor();
}

void PrintManager::printWarning(const string& warning) const noexcept {
    applyColor(_typeToColor.at(ColorType::WARNING));
    cout << "Warning: ";
    
    applyColor(_typeToColor.at(ColorType::INFORMATION));
    cout << warning << endl;

    resetColor();
}

void PrintManager::printParameter(const std::string& parameterName, const std::string& parameterValue) const noexcept {
    applyColor(_typeToColor.at(ColorType::PARAMETER));
    
    size_t width = (_parameterWidth < parameterName.size()) ?
        _parameterWidth : _parameterWidth - parameterName.size();
    cout << parameterName << left << setw(width) << ':';

    applyColor(_typeToColor.at(ColorType::INFORMATION));
    cout << parameterValue << endl;

    resetColor();
}

void PrintManager::applyColor(Color color) const noexcept {
    SetConsoleTextAttribute(_consoleHandle, static_cast<WORD>(color));
}

void PrintManager::resetColor() const noexcept {
    Color defaultColor = _typeToColor.at(ColorType::DEFAULT);
    SetConsoleTextAttribute(_consoleHandle, static_cast<WORD>(defaultColor));
}
