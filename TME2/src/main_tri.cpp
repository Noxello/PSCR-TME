#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include "hashtable.hpp"

using namespace std;
using namespace std::chrono;

int main () {

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;

	HashTable<string, int> table;

	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	int *adresse_res, res;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		adresse_res = table.get(word);
		res = adresse_res == nullptr ? 1 : ++(*adresse_res);
		table.put(word, res);
		

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";



    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Total de mots differents " << table.size()  << endl;

	string mot = "war";
	adresse_res = table.get(mot);
	res = adresse_res == nullptr ? 0 : *adresse_res;

	cout << "Nombre d'occurences war " << res << endl;

	mot = "peace";
	adresse_res = table.get(mot);
	res = adresse_res == nullptr ? 0 : *adresse_res;

	cout << "Nombre d'occurences peace " << res << endl;

	mot= "toto";
	adresse_res = table.get(mot);
	res = adresse_res == nullptr ? 0 : *adresse_res;
	cout << "Nombre d'occurences toto " << res << endl;

	vector<pair<string,int>> *occurences = new vector<pair<string,int>>(30000);
	auto buckets = table.getBuckets();
	for(auto &liste : *buckets){
		occurences->insert(occurences->end(), liste.begin(), liste.end());
	}
	std::sort(occurences->begin(), occurences->end(), [] (const pair<string,int> &a, const pair<string,int> &b){return a.second > b.second;});

	for(int i = 0; i<10; i++){
		cout << "Mot nb " << i << " " << (*occurences)[i].first <<" nb occurences " << (*occurences)[i].second << endl;
	}
    return 0;
}


