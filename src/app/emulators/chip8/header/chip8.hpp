#ifndef EMULATORS_CHIP8_HPP
#define EMULATORS_CHIP8_HPP

#include <core.hpp>

namespace Emulators
{
    class CHIP8 : public Core::State
    {
    private:

    public:
        void draw() override;
        void update(double dt) override;
    };
};

#endif