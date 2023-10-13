#include "Banque.h"
#include  <chrono>
#include <iostream>
#define SOLDE_INITIAL 1000
#define NB_CLIENTS 20
using namespace std;

const int NB_THREAD = 10;

void work(pr::Banque &b){
	int i = ::rand() % NB_CLIENTS;
	int j;
	do{
		j = ::rand() % NB_CLIENTS;
	}while(i==j);
	int montant = ::rand() % 100 + 1;
	int duree = ::rand() % 21;

	b.transfert(i,j,montant);
	this_thread::sleep_for(std::chrono::milliseconds(duree));
	// this_thread::sleep_for(std::chrono::seconds(duree));
}

int main () {

	pr::Banque b(NB_CLIENTS, SOLDE_INITIAL);
	vector<thread> threads;
	for(int i = 0; i< NB_THREAD; ++i){
		threads.emplace_back(work, ref(b));
	}
	
	this_thread::sleep_for(std::chrono::milliseconds(10));

	cout << "Resultat du bilan comptable avant join : " <<  (b.comptabiliser(NB_CLIENTS * SOLDE_INITIAL) ? "ok" : "pas ok") << endl;

	for (auto & t : threads) {
		t.join();
	}

	cout << "Resultat du bilan comptable apres join : " << (b.comptabiliser(NB_CLIENTS * SOLDE_INITIAL) ? "ok" : "pas ok") << endl;

	return 0;
}
