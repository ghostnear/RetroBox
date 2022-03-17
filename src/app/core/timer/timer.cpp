#include "timer.hpp"

namespace Core
{
    Timer::Timer()
    {
        // Default values
        reset();
    };

    void Timer::reset()
    {
        // Default values
        now = last = SDL_GetPerformanceCounter();
        deltaTime = 0;
    }

    void Timer::update()
    {
        // Update last timer and current timer
        last = now;
        now = SDL_GetPerformanceCounter();

        // Calculate the delta timer based on the new values (in seconds)
        deltaTime = (now - last) * 1.0 / SDL_GetPerformanceFrequency();
    }

    double Timer::getDelta()
    {
        // Returns the time delay in seconds
        return deltaTime;
    }
};