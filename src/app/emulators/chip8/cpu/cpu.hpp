#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP

#include <core.hpp>
#include <queue>
#include "../state/state.hpp"

namespace Emulators
{
    namespace Components
    {
        class CHIP8CPU
        {
        protected:
            CHIP8State* state;
            std::deque<std::string> executionLog;
        public:
            void attachState(CHIP8State* newState) { state = newState; }
            void addToLog(std::string path) {
                if(executionLog.empty() || executionLog.front() != path)
                {
                    executionLog.push_front(path);
                    if(executionLog.size() > 10)
                        executionLog.pop_back();
                }
            }
            void printLog()
            {
                if(ImGui::CollapsingHeader("Execution logs"))
                {
                    if(!executionLog.empty())
                        for(auto x : executionLog)
                            ImGui::Text("%s", x.c_str());
                }
            }
            virtual void step() = 0;
            virtual void update(double dt) = 0;
        };

        enum CHIP8ExecutionMode
        {
            Interpreter = 0
        };
    };
};

#endif