#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int counter {0};
std::mutex dataMut;
void task(){
    std::lock_guard dataLck(dataMut);
    for(int i=0;i<100'000;i++){
        ++counter;
    }
}
int main() {
    std::cout << "Integer Operation and Threads" << std::endl;
    std::vector<std::thread> threads;
    for(int i =0;i<10;i++){
        threads.emplace_back(task);
    }
    for(auto& t : threads){
        t.join();
    }
    std::cout << counter << std::endl;
    return 0;
}
