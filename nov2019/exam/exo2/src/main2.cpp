#include "Semaphore.h"
#include <thread>
#include <vector>
#include <atomic>
// TODO : classe à modifier
class Data {
	std::vector<int> values;
	mutable pr::Semaphore sRead;
	mutable std::atomic<bool> isWriting;
	mutable std::atomic<int> cptReading;
	mutable std::mutex m;
	mutable std::condition_variable cv;

public :
	Data(): sRead(256), isWriting(false), cptReading(0) {}

	int read() const {
		sRead.acquire(1);

		std::unique_lock<std::mutex> l(m);
		while(isWriting){
			cv.wait(l);
		}
		cptReading++;
		l.unlock();

		int res;
		if (values.empty())
			res = 0;
		else
			res = values[rand()%values.size()];

		cptReading--;
		sRead.release(1);
		cv.notify_all();
		return res;
	}
	void write() {
		std::unique_lock<std::mutex> l(m);
		while(cptReading != 0){
			cv.wait(l);
		}
		isWriting = true;
		values.push_back(rand());
		isWriting = false;
		cv.notify_all();
	}
};

// Pas de modifications dans la suite.
void worker(Data & data) {
	for (int i=0; i < 20 ; i++) {
		auto r = ::rand() % 1000 ; // 0 to 1 sec
		std::this_thread::sleep_for (std::chrono::milliseconds(r));
		if (r % 2)
			auto lu = data.read();
		else
			data.write();
	}
}

int main () {
	// a faire varier
	const int NBTHREAD=10;

	// le data partagé
	Data d;

	std::vector<std::thread> threads;
	for (int i=0; i < NBTHREAD; i++)
		threads.emplace_back(worker,std::ref(d));

	for (auto & t: threads)
		t.join();
	return 0;
}

