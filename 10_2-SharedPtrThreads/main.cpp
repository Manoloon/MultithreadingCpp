#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
auto shr1 = std::make_shared<int>(42);
std::mutex mut;
void func(){
    std::lock_guard<std::mutex> lck(mut);
    auto shr2 = shr1;
    *shr1 = *shr1 * 2;
    std::cout << "func1 id : " << std::this_thread::get_id() << " shared :" << *shr2 << std::endl;
    std::cout << "func1 : " << " shared 1 :" << *shr1 << std::endl;
}
void func2(){
    std::lock_guard<std::mutex> lck(mut);
    auto shr3 = shr1;
    std::cout << "func2 id : " << std::this_thread::get_id() << " shared :" << *shr3 << std::endl;
}
int main() {
    std::cout << "shr1 :" << *shr1 << std::endl;
    std::thread thr1(func);
    std::thread thr2(func2);
    thr1.join();
    thr2.join();
    return 0;
}
