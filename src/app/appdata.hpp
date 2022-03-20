#ifndef APPDATA_HPP
#define APPDATA_HPP

#define OWARI_VERSION_MAJOR   std::string("0")
#define OWARI_VERSION_MINOR   std::string("0")
#define OWARI_VERSION_PATCH   std::string("1")
#define OWARI_VERSION_SPECIAL std::string("alpha")
#define OWARI_VERSION \
    (OWARI_VERSION_MAJOR + "." + OWARI_VERSION_MINOR + "." + OWARI_VERSION_PATCH + \
    ((OWARI_VERSION_SPECIAL != "") ? "-": "") + OWARI_VERSION_SPECIAL)

#endif