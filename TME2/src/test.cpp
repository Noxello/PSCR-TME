#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include "hashtable.hpp"

int main(int argc, char const *argv[]){
    
    HashTable<string, int>  table;
    table.put("HELLO",13);
    table.put("bonjour", 13);

    for(auto elem : table){
        cout << elem.first << " " << elem.second << endl;
    }
    return 0;
}
