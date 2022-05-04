#ifndef CORE_LOCALE_HPP
#define CORE_LOCALE_HPP

#include <string>

//TODO: Coming Soon :tm:

namespace Core
{
    #define LOCALE Locale::get()

    // Locale singleton handler
    class Locale
    {
        private:
            // Unimplemented singleton functions
            Locale() {}

            // Class properties
            std::string locale_name;

        public:
            // Instance getter
            static Locale& get()
            {
                static Locale instance;
                return instance;
            }

            // These have to be public, but they shouldn't do anything
            Locale(Locale const&)          = delete;
            void operator=(Locale const&)  = delete;

            // Get current locale
            std::string getLocale();
    };
};

#endif