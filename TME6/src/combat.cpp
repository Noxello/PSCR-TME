#include <ctime>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"

int vie = 3;

using namespace std;

void attaque(pid_t adversaire){
    struct sigaction action;
    action.sa_handler = [](int i){ vie--; 
        cout << "points de vie proc " << getpid() << " : "<< vie << endl;
        if(vie == 0){
            cout << "fin proc " << getpid() << endl;
            _exit(1);
        }};
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, nullptr);

    if(kill(adversaire, SIGINT) == -1)
        exit(0);
    cout << "kill envoye par " << getpid() << endl;

    randsleep();
}
void defense(){
    struct sigaction action;
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, nullptr);

    randsleep();
}
void combat(pid_t adversaire){
    while(true){
        attaque(adversaire);
        defense();
    }
}
int main(int argc, char const *argv[]){
    pid_t adv = fork();

    if(adv == 0)
        adv = getppid();

    // sigset_t masks;
    // sigemptyset(&masks);
    // sigaddset(&masks, SIGINT);
    // sigprocmask(SIG_BLOCK, &masks, nullptr);

    sleep(1);
    cout << "debut combat" << endl;
    combat(adv);

    return 0;
}
