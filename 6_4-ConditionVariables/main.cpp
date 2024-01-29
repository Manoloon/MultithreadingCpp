/*
 * Rewrite the first condition variable example from the video to use a boolean flag instead of a condition variable.
 * Your program must not contain any data race, deadlock or livelock conditions.
 *
 */

#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
condition_variable cv;
bool dataIsReady=false;
string sdata{"Empty"};

// Waiting thread
void reader() {
	unique_lock<std::mutex> guard(mut);           // Acquire lock
    while (!dataIsReady){
        guard.unlock();
        std::this_thread::sleep_for(10ms);
        cout << "Data is " << sdata << endl;
        guard.lock();
    }

    cout << "Data is " << sdata << endl;
   // cv.wait(guard);                                // Wait for condition variable to be notified
	          // Wake up and use the new value
}

// Modyifing thread
void writer() {
    cout << "Writing data..." << endl;
    {
		lock_guard<std::mutex> lg(mut);            // Acquire lock
		std::this_thread::sleep_for(2s);           // Pretend to be busy...
		sdata = "Populated";// Modify the data
        dataIsReady =true;
	}
	//cv.notify_one();                               // Notify the condition variable
}

int main() {
	cout << "Data is " << sdata << endl;
	thread read{reader};
    thread write{writer};
	/*
	// If the writer thread finishes before the reader thread starts, the notification is lost
	thread write{writer};
	std::this_thread::sleep_for(500ms);
	thread read{reader};
	*/
	write.join();
	read.join();
}