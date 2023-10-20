#include "Queue.h"
#include "Job.h"
#include "Pool.h"
#include <vector>
#include <thread>

using namespace std;
using namespace pr;

void poolWorker(Queue<Job> &queue){
    Job* j;
    while((j = queue.pop()) != nullptr){
        j->run();
        delete j;
    }
}
pr::Pool::Pool(int qsize):queue(qsize), threads() {}

void pr::Pool::start (int nbthread){
    for(int i = 0; i < nbthread; i++)
        threads.emplace_back(poolWorker, ref(queue));
}
void pr::Pool::submit (Job * job){
    queue.push(job);
}
void pr::Pool::stop(){
    queue.setBlocking(false);
    for(auto &t: threads){
        t.join();
    }
}


