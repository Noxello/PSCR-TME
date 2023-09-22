#pragma once
#include <ostream>

namespace pr{
    size_t length(const char* str);
    char* newcopy(const char* str);

    class String{
        const char *str;

        public :
            String(const char* str = "");
            String(String &s);
            ~String(){
                delete[] str;
            };

            size_t length() const;
            void print() const;
    };
    std::ostream & operator<< (std::ostream & os, const String & s);
    String & operator=(const String & s);
}