#ifndef EMULATORS_CHIP8_HPP
#define EMULATORS_CHIP8_HPP

#include <core.hpp>

namespace Emulators
{
    class CHIP8 : public Core::State
    {
    private:
        double timer = 0;
    public:
        void draw() override;
        void update(double dt) override;
    };
};

#endif