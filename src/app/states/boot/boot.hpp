#ifndef STATE_BOOT_HPP
#define STATE_BOOT_HPP

#include <core.hpp>

namespace States
{
    class Boot : public Core::State
    {
    public:
        void init() override;
        void draw() override;
        void update(double dt) override;
    };
};

#endif