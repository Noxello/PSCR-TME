#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include <vector>

using namespace std;
using namespace std::chrono;

pair<string,int>* isInVector(vector<pair<string,int>> *tab, string s){
	for (auto &elem : *tab){
		if(elem.first == s)
			return &elem;
	}
	return nullptr;
}

int main () {
	

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	vector<pair<string,int>> *tab = new vector<pair<string,int>>;
	pair<string,int> *tuple;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// word est maintenant "tout propre"

		tuple = isInVector(tab, word);
		if(tuple == nullptr)
			tab->push_back(std::make_pair(word,1));
		else
			(tuple->second)++;

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

	int res;
    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Nombre de mots differents : " << tab->size() << endl;
	
	tuple = isInVector(tab, "war");
	res = tuple == nullptr ? 0 : tuple->second;

	cout << "Nombre d'occurences war " << res << endl;

	tuple = isInVector(tab, "peace");
	res = tuple == nullptr ? 0 : tuple->second;
	cout << "Nombre d'occurences peace " << res << endl;


	tuple = isInVector(tab, "toto");
	res = tuple == nullptr ? 0 : tuple->second;
	cout << "Nombre d'occurences toto " << res << endl;


    return 0;
}


