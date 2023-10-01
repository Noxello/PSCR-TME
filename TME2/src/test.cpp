#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include "hashtable.hpp"

int main(int argc, char const *argv[]){
    
    HashTable<string, int>  table;
    table.put("test",0);
    string word = "test";
    int *adresse_res = table.get(word);

    if(adresse_res == nullptr)
	    table.put(word, 12);
	else{
        std::cout << "adresse_res avant: " << *adresse_res << std::endl;
		(*adresse_res)++; 
        std::cout << "adresse_res apres: " << *adresse_res << std::endl;

    }
    

    int *res = table.get(word);
    std::cout << "adresse res " << *adresse_res << std::endl;
    std::cout << "res " << *res << std::endl;
    std::cout <<"test 1: " <<  (adresse_res == res) << std::endl;
    std::cout <<"test 2: " <<  (*adresse_res == *res) << std::endl;
    return 0;
}
