#ifndef BYTEPUSHER_VM_HPP
#define BYTEPUSHER_VM_HPP

#include <queue>
#include <core.hpp>
#include "../state/state.hpp"

namespace Emulators
{
    namespace Components
    {
        class BytePusherVM
        {
        protected:
            BytePusherState* state;
        public:
            void attachState(BytePusherState* newState) { state = newState; }
            void start();
            void stop();
            void step();
            void update(double dt);
        };
    };
};

#endif