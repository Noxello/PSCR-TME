#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <semaphore.h>            
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <vector>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]){
    int pipeFD[2];
    pipe(pipeFD);
    
    vector<char const*> args1;
    vector<char const*> args2;
    int i;
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i],"|")==0)
            break;

        args1.push_back(argv[i]);
    }
    for(i++; i < argc; i++){
        args2.push_back(argv[i]);
    }

    const char * tabArgs1[args1.size() + 1];
    char const * tabArgs2[args2.size() + 1];
    tabArgs1[args1.size()] = nullptr;
    tabArgs2[args2.size()] = nullptr;

    for(int i = 0; i < args1.size(); i++){
        tabArgs1[i] = args1[i];
    }
    for(int i = 0; i < args2.size(); i++){
        tabArgs2[i] = args2[i];
    }

    pid_t p = fork();

    if(p){//pere, execute la premiere commande
        // cout << "exec pere " << tabArgs1[0] << endl; 
        dup2(pipeFD[1], STDOUT_FILENO);
        close(pipeFD[0]);
        close(pipeFD[1]);
        execv(tabArgs1[0], const_cast<char * const *>(tabArgs1));
        perror("execv");
        exit(3);

    }else{//fils, execute la deuxieme commande
        // cout << "exec fils " << tabArgs2[0] << endl;
        dup2(pipeFD[0], STDIN_FILENO);
        close(pipeFD[0]);
        close(pipeFD[1]);
        execv(tabArgs2[0], const_cast<char * const *>(tabArgs2));
        perror ("execv");
        exit(3);

    }
    return 0;
}
