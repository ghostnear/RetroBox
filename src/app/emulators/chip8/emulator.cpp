#include "header/chip8.hpp"

namespace Emulators
{
    void CHIP8::draw()
    {

    }
    
    void CHIP8::update(double dt)
    {
        timer += dt;
        if(timer >= 3) exit(0);
    }
};