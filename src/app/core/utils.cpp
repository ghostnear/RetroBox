#include "core.hpp"

namespace Core
{
    namespace Utils
    {
        std::string convertToHex(int n, int width)
        {
            std::stringstream stream;
            stream << std::hex << std::fixed << std::setfill('0') << std::setw(width)  << std::uppercase << n;
            return stream.str();
        }
    };
}