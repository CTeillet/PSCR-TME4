#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {
	std::mutex m;
void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	m.lock();
	comptes[deb].lock();
	comptes[cred].lock();
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	comptes[deb].unlock();
	comptes[cred].unlock();
	m.unlock();
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	m.lock();
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	m.unlock();
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}
