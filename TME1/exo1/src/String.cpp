#include "String.hh"

namespace pr{
    size_t length(const char* str){
        size_t len = 0;
        while(str[len++]);
        return len;
    }
    char* newcopy(const char* str){
        size_t size = length(str) + 1;
        // +1 for '\0'
        char* res = new char[size];
        
        for(int i =0; i < size; i++)
            res[i] = str[i];
        
        return res;
    }

    
    String::String(const char* str):str(newcopy(str)){}
    String::String(String &s){
        str = newcopy(s.str);
    }

    size_t String::length() const{
        return pr::length(str);
    }
    String::print() const{
        std::cout << str << std::endl;
    }
    std::ostream & operator<< (std::ostream & os, const String & s){
        os<<s.str;
        return os;
    }
    String & operator=(const String & s){
        delete[] str;
        this.str = newcopy(s.str);
    }


}