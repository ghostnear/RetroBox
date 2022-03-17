#ifndef CORE_STATE_HPP
#define CORE_STATE_HPP

#include "../window/window.hpp"

namespace Core
{
    class State
    {
    public:
        virtual void draw() = 0;
        virtual void update(double dt) = 0;
    };
};

#endif