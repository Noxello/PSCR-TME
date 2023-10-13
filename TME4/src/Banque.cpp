#include "Banque.h"
#include "Compte.h"
#include <iostream>

using namespace std;

namespace pr {
	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];

		auto &mDeb = debiteur.getMutex();
		auto &mCred = crediteur.getMutex();

		m.lock();
		std::lock(mDeb,mCred);
		m.unlock();
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
		mDeb.unlock();
		mCred.unlock();
	}
	size_t Banque::size() const {
		return comptes.size();
	}
	bool Banque::comptabiliser (int attendu) const {
		int bilan = 0;
		int id = 0;
		for (const auto & compte : comptes) {
			compte.getMutex().lock();
			if (compte.getSolde() < 0) {
				cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
			}
			bilan += compte.getSolde();
			id++;
		}
		for(const auto& compte: comptes){
			compte.getMutex().unlock();
		}
		if (bilan != attendu) {
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}
}
