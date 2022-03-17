#ifndef CORE_TIMER_HPP
#define CORE_TIMER_HPP

#include <SDL.h>

namespace Core
{
    class Timer
    {
        uint64_t now, last;
        double deltaTime;

    public:
        // Constructor
        Timer();

        // Update the timer
        void update();

        // Resets the clock
        void reset();

        // Get the delta time
        double getDelta();
    };
};

#endif