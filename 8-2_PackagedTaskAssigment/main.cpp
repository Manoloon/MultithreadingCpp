//lock-free queue class
#include <vector>
#include <iostream>
#include <thread>
#include <future>
using namespace std::chrono_literals;
int main() {
    std::packaged_task<int(int,int)> ptest([](int a, int b){
        std::this_thread::sleep_for(2s);
        return a * b;
    });
    std::future<int> fut = ptest.get_future();
    //ptest(2,3);
    // remember that this type of class is only movable.
    std::thread thr(std::move(ptest),2,8);
    thr.join();
    std::cout << "waiting the 2s :" << std::endl;
    std::cout  << fut.get() << std::endl;

    return 0;
}