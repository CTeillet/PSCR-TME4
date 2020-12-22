#include "Banque.h"
#include <iostream>

using namespace std;
//using namespace pr;

const int NB_THREAD = 20;
const int NB_CMP = 1000;
const int SOLDE_BASE = 1000;

void transaction(pr::Banque& b) {
	int i = ::rand() % b.size();
	int j = ::rand() % b.size();
	int m = ::rand() % 101 + 1;
	b.transfert(i, j, m);
	int r = ::rand() % 2000;
	std::this_thread::sleep_for(std::chrono::milliseconds(r));
}

void comptabiliser(pr::Banque& b) {
	b.comptabiliser(NB_CMP * SOLDE_BASE);
}

int main() {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	pr::Banque b = pr::Banque(NB_CMP, SOLDE_BASE);
	::srand(::time(nullptr));

	thread comptable(comptabiliser, std::ref(b));

	for (int i = 0; i < NB_THREAD; ++i) {
		threads.emplace_back(transaction, std::ref(b));
		//std::cout << i << std::endl;
	}
	for (auto& t : threads) {
		t.join();
	}

	comptable.join();

	// TODO : tester solde = NB_THREAD * SOLDE_BASE
	//std::cout << std::boolalpha << b.comptabiliser(NB_CMP*SOLDE_BASE) << std::endl;
	return 0;
}

