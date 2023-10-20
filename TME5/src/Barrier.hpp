#pragma once
#include <mutex>
#include <condition_variable>
using namespace std;

namespace pr{
    class Barrier{
        int N;
        int cpt;
        condition_variable cv;
        mutex m;

        public:
            Barrier(const int N);
            void done();
            void wait();
    };
}