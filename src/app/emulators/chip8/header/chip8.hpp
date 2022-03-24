#ifndef EMULATORS_CHIP8_HPP
#define EMULATORS_CHIP8_HPP

#include <string>
#include <fstream>
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

        // Output handling
        uint32_t lscreen_w = 0, lscreen_h = 0;
        SDL_Texture* tex = nullptr;
    public:
        void init() override;
        void draw() override;
        void update(double dt) override;
        void loadROM(std::string path);
    };
};

#endif