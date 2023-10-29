#pragma once

#include <mutex>
#include <condition_variable>
namespace pr {
	class Semaphore {
		int compteur;
		std::condition_variable cv;
		std::mutex m;
		
	public :
		Semaphore(int initial): compteur(initial), cv(), m(){	}

		void acquire(int qte){
			std::unique_lock<std::mutex> l(m);

			while(compteur < qte){
				cv.wait(l);
			}
			compteur-=qte;
		}
		
		void release(int qte){
			std::unique_lock<std::mutex> l(m);

			compteur+=qte;

			cv.notify_all();
		}
	};

}
