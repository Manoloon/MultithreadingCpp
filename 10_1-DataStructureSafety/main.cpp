#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
std::vector<int> vec1(20000);
std::mutex mut;
void func1() {
    // without this locks the threads interleave
    std::lock_guard lck(mut);
    for (int i = 0; i < 10000; i++) {
        vec1.emplace_back(i);
    }
}

void func2() {
    // without this locks the threads interleave
    std::lock_guard lck(mut);
    for (int i = 10000; i < 20000; i++) {
        vec1.emplace_back(i);
    }
}

int main() {
    std::thread thr1(&func1);
    std::thread thr2(&func2);
    thr1.join();
    thr2.join();
    for(auto i : vec1) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    return 0;
}
