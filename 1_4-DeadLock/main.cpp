#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

std::mutex mut1;
std::mutex mut2;
// deadlock will happen is task1 is locking mutex 1 first and Task2 try to lock first mutex 2.
// to avoid this task1 lock mutex1 and then mutex2 , and task2 , first mutex1 , then mutex2 .
// a better approach is to lock all mutex on the same operation at once using std::scoped_lock()
void Task1(){
    std::cout << "Thread 1 trying to lock mutex 1"  << std::endl;
    //std::lock_guard guard_lck(mut1);
    std::scoped_lock multiLock(mut1,mut2);
    std::cout << "Thread 1 has locked mutex 1"  << std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread 1 trying to lock mutex 2"  << std::endl;
    //std::lock_guard guard_lck2(mut2);
    std::cout << "Thread 1 has locked mutex 2"  << std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread 1 has release all mutex"  << std::endl;
}
void Task2(){
    std::cout << "Thread 2 trying to lock mutex 1"  << std::endl;
    //std::lock_guard guard_lck(mut1);
    std::scoped_lock multiLock(mut1,mut2);
    std::cout << "Thread 2 has locked mutex 1"  << std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread 2 trying to lock mutex 2"  << std::endl;
    //std::lock_guard guard_lck2(mut2);
    std::cout << "Thread 2 has locked mutex 2"  << std::endl;
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread 2 has release all mutex"  << std::endl;
}
int main() {
    std::thread thr(Task1);
    std::thread thr2(Task2);
    thr.join();
    thr2.join();
    return 0;
}
