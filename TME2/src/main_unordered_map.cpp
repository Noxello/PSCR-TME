#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <forward_list>
#include "hashtable.hpp"
#include "algorithm.hpp"

using namespace std;
using namespace std::chrono;

int main () {

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	
	std::unordered_map<string, int> table;

	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	int res;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		auto elem = table.find(word);
		res = elem == table.end() ? 1 : ++(elem->second);
		table.insert(std::unordered_map<string, int>::value_type(word, res));
		

		// // word est maintenant "tout propre"
		// if (nombre_lu % 100 == 0)
		// 	// on affiche un mot "propre" sur 100
		// 	cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";



    cout << "Found a total of " << nombre_lu << " words." << endl;

	cout << "Total de mots differents en utilisant algorithm.hpp" << count(table.begin(), table.end()) << endl;

	cout << "Total de mots differents en utilisant le compteur " << table.size()  << endl;

	string mot = "war";
	try{
		int &res_ref = table.at(mot);
		res = res_ref;
	}catch(std::out_of_range const&){
		res = 0;
	}
	cout << "Nombre d'occurences war " << res << endl;

	mot = "peace";
	try{
		int &res_ref = table.at(mot);
		res = res_ref;
	}catch(std::out_of_range const&){
		res = 0;
	}

	cout << "Nombre d'occurences peace " << res << endl;

	mot= "toto";
	try{
		int & res_ref = table.at(mot);
		res = res_ref;
	}catch(std::out_of_range const&){
		res = 0;
	}
	cout << "Nombre d'occurences toto " << res << endl;

	vector<pair<string,int>> occurences(30000);

	for(auto elem : table){
		occurences.push_back(elem);
	}

	// for(auto it = table.begin(); it != table.end(); ++it){
	// 	occurences.push_back(*it);
	// }

	std::sort(occurences.begin(), occurences.end(), [] (const pair<string,int> &a, const pair<string,int> &b){return a.second > b.second;});

	for(int i = 0; i<10; i++){
		cout << "Mot position " << i << " : " << occurences[i].first <<" nb occurences : " << occurences[i].second << endl;
	}


	std::unordered_map<int, forward_list<string>> table_frequences(10000);
	for(auto paire_string_int : table){
		string mot = paire_string_int.first;
		int freq =  paire_string_int.second;
		
		auto it_liste =	table_frequences.find(freq);
		if(it_liste == table_frequences.end()){
			std::forward_list<string> liste = {mot};
			table_frequences.insert(std::unordered_map<int, forward_list<string>>::value_type(freq, liste));
		}else{
			it_liste->second.push_front(mot);
		}
	}
	
	forward_list<int> liste_frequences = {0, 100, 10513, 34562};
	for(int freq : liste_frequences){
		auto it_liste = table_frequences.find(freq);
		
		if(it_liste == table_frequences.end()){
			cout << "Aucun mot de frequence " << freq << endl; 
		}else{
			cout << "Mots de frequence " << freq << " : ";
			for(auto mot : it_liste->second){
				cout << mot << " ";
			}
			cout << endl;
		}
	}
    return 0;
}


