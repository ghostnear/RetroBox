#ifndef CORE_HPP
#define CORE_HPP

#include <sstream>
#include <iomanip>
#include <../timer/timer.hpp>
#include <../window/window.hpp>
#include <../states/statemanager.hpp>
#include <../argparser/argparser.hpp>

namespace Core
{
    namespace Utils
    {
        std::string convertToHex(int n, int w);
    };
}

#endif