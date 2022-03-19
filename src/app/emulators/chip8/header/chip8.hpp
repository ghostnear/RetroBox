#ifndef EMULATORS_CHIP8_HPP
#define EMULATORS_CHIP8_HPP

#include <core.hpp>
#include "../cpu/interpreter.hpp"

namespace Emulators
{
    using namespace Components;

    class CHIP8 : public Core::State
    {
    private:
        CHIP8State* state;
        CHIP8CPU* cpu;
    public:
        void init() override;
        void draw() override;
        void update(double dt) override;
    };
};

#endif