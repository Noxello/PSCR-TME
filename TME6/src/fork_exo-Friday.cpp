#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nbfils = 1;
	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		nbfils = 0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				nbfils = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else
				nbfils++;
		}
	}
	while(nbfils--)
		wait(NULL);
	return 0;
}
