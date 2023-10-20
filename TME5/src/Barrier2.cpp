#include <mutex>
#include <condition_variable>
#include "Barrier.hpp"

using namespace std;

pr::Barrier::Barrier( int N): N(N), cpt(0), cv(), m(){}

void pr::Barrier::done(){
    unique_lock<mutex> l(m);
    cpt++;
    if (cpt == N)
        cv.notify_all();   
}
void pr::Barrier::wait(){
    unique_lock<mutex> l(m);
    if (cpt < N){
        cv.wait(l);
    }
}
