#ifndef EMULATORS_BYTEPUSHER_HPP
#define EMULATORS_BYTEPUSHER_HPP

#include <string>
#include <fstream>
#include <core.hpp>
#include "../VM/vm.hpp"
#include "../state/state.hpp"

namespace Emulators
{
    using namespace Components;

    class BytePusher : public Core::State
    {
    private:
        BytePusherState* state;
        BytePusherVM* vm;

        // Output handling
        SDL_Texture* tex = nullptr;
    public:
        void init() override;
        void draw() override;
        void update(double dt) override;
        void loadROM(std::string path);
    };
};

#endif