#ifndef CORE_STATE_HPP
#define CORE_STATE_HPP

#include "../window/window.hpp"

namespace Core
{
    class StateManager;

    class State
    {
    protected:
        StateManager* parent;
    public:
        void setParent(StateManager* newParent) { parent = newParent; }
        virtual void init() = 0;
        virtual void draw() = 0;
        virtual void update(double dt) = 0;
    };
};

#endif