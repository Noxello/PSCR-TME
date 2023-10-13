#include "Compte.h"

using namespace std;

namespace pr {
	void Compte::crediter (unsigned int val) {
		m.lock();
		solde+=val ;
		m.unlock();
	}
	bool Compte::debiter (unsigned int val) {
		m.lock();
		bool doit = solde >= (int) val;
		if (doit) {
			solde-=val ;
		}
		m.unlock();
		return doit;
	}
	int Compte::getSolde() const  {
		m.lock();
		int res = solde;
		m.unlock();
		return res;
	}
	// NB : vector exige Copyable, mais mutex ne l'est pas...
	Compte::Compte(const Compte & other) {
		other.m.lock();
		solde = other.solde;
		other.m.unlock();
	}
	recursive_mutex &Compte::getMutex() const{
		return m;
	}
}
