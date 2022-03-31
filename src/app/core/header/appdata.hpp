#ifndef APPDATA_HPP
#define APPDATA_HPP

#define APP_NAME            std::string("RetroBox")
#define APP_VERSION_MAJOR   std::string("0")
#define APP_VERSION_MINOR   std::string("0")
#define APP_VERSION_PATCH   std::string("1")
#define APP_VERSION_SPECIAL std::string("alpha")
#define APP_VERSION \
    (APP_VERSION_MAJOR + "." + APP_VERSION_MINOR + "." + APP_VERSION_PATCH + \
    ((APP_VERSION_SPECIAL != "") ? "-": "") + APP_VERSION_SPECIAL)

#endif