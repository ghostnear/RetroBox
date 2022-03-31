#include "argparser.hpp"

namespace Core
{
    ArgParser::ArgParser(int argc, char* argv[])
    {
        // Auxiliary variables
        static const char *const usages[] = {
            "RetroBox [options] [[--] args]",
            "RetroBox [options]",
            NULL,
        };
        const char *type = NULL;
        const char *path = NULL;

        // Init default values
        versionMode = false;
        helpMode = false;
        emulator = "";
        romPath = "";

        // Options
        struct argparse_option options[] = {
            OPT_GROUP("Main app options:"),
            OPT_BOOLEAN('h', "help", &helpMode, "Show this message.", argparse_help_cb, 0, OPT_NONEG),
            OPT_BOOLEAN('v', "version", &versionMode, "Show the app version.", NULL, 0, 0),
            OPT_GROUP("Emulator options:"),
            OPT_STRING('e', "emulator", &type, "Select what emulator to use when loading the ROM.", NULL, 0, 0),
            OPT_STRING('p', "path", &path, "Select the path of the ROM.", NULL, 0, 0),
            OPT_END(),
        };

        // Initialise the parsing
        struct argparse argparse;
        argparse_init(&argparse, options, usages, 0);

        // Program description in the help option
        argparse_describe(&argparse, "\nA multiplatform emulator. (WIP)", "");
        
        // Calculate the actual number of arguments after execution
        argCount = argc = argparse_parse(&argparse, argc, (const char** const&)argv);

        // Save the parsed variables
        if(type != nullptr)
            emulator = std::string(type);
        if(path != nullptr)
            romPath = std::string(path);
    }
};