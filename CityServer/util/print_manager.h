#pragma once

#include <string>
#include <windows.h>
#include <unordered_map>

#include "singleton.h"

namespace util {

    enum class ColorType {
        TITLE,
        PARAMETER,
        INFORMATION,
        WARNING,
        DEFAULT,
    };

    enum class Color
    {
        BLACK                           = 0,
        BLUE                            = 1,
        GREEN                           = 2,
        CYAN                            = 3,
        RED                             = 4,
        MAGENTA                         = 5,
        BROWN                           = 6,
        LIGHT_GRAY                      = 7,
        DARK_GRAY                       = 8,
        LIGHT_BLUE                      = 9,
        LIGHT_GREEN                     = 10,
        LIGHT_CYAN                      = 11,
        LIGHT_RED                       = 12,
        LIGHT_MAGENTA                   = 13,
        YELLOW                          = 14,
        WHITE                           = 15,
    };
    
    using ColorByType                   = std::unordered_map<ColorType, Color>;

    class PrintManager : public Singleton<PrintManager> {
    public:
        friend class Singleton<PrintManager>;
        
        void                            setColor(ColorType colorType, Color color) noexcept;
        void                            setParameterWidth(size_t width) noexcept;
        void                            printTitle(const std::string& title) const noexcept;
        void                            printWarning(const std::string& warning) const noexcept;
        void                            printParameter(const std::string& parameterName, const std::string& parameterValue) const noexcept;

    private:
        PrintManager() noexcept;

        void                            applyColor(Color color) const noexcept;
        void                            resetColor() const noexcept;

        HANDLE                          _consoleHandle;
        ColorByType                     _typeToColor;
        size_t                          _parameterWidth;
    };

}
