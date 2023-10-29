#include "Semaphore.h"
#include <iostream>
#include <thread>

void pinger(int n, pr::Semaphore& sPing, pr::Semaphore &sPong) {
	for (int i=0; i < n ; i++) {
		sPing.acquire(1);
		std::cout << "ping " << std::endl;
		sPong.release(1);
	}
}

void ponger(int n, pr::Semaphore& sPing, pr::Semaphore &sPong) {
	for (int i=0; i < n ; i++) {
		sPong.acquire(1);
		std::cout << "pong " << std::endl;
		sPing.release(1);
	}
}

int main () {
	// a faire varier si on le souhaite
	const int NBITER = 3;

	pr::Semaphore sPing(1);
	pr::Semaphore sPong(0);

	std::thread tPing(pinger, NBITER, std::ref(sPing), std::ref(sPong));
	std::thread tPong(ponger, NBITER, std::ref(sPing), std::ref(sPong));
	// TODO : instancier un thread pinger et un thread ponger avec n=NBITER

	// TODO : terminaison et sortie propre
	tPing.join();
	tPong.join();
	

	return 0;
}

