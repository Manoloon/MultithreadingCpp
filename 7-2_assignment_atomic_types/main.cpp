#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>

class some_type {
	// ...
public:
	void do_it() { std::cout << "hello"; }
};

std::atomic<some_type*> ptr = nullptr;            // Variable to be lazily initialized
std::mutex process_mutex;

void process() {
    if (!ptr) {                     // First check of ptr
        std::lock_guard<std::mutex> lk(process_mutex);
        
        if (!ptr)                  // Second check of ptr
            ptr = new some_type;   // Initialize ptr
    }
    some_type* test = ptr;
    test->do_it();
}
int main(){
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join();
    thr2.join();
}
