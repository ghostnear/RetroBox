#ifndef CORE_ARGPARSER_HPP
#define CORE_ARGPARSER_HPP

#include <string>
#include <argparse.h>

namespace Core
{
    class ArgParser
    {
    private:
        std::string emulator, romPath;
        int argCount;
        bool helpMode;
        bool versionMode;
    public:
        // Constructor
        ArgParser(int argc, char* argv[]);

        // Getters
        std::string getEmu() { return emulator; }
        std::string getPath() { return romPath; }
        bool getVersionMode() { return versionMode; }
        bool getHelpMode() { return helpMode; }
        int getCount() { return argCount; }
    };
};

#endif