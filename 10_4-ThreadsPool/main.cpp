#include <future>
#include <iostream>
#include <string>
#include "threadsPool.h"

using namespace std::chrono_literals;
void task(){
    std::cout << "Calling task from ID : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
}
int main() {
    threadsPool TPool;
    std::cout << "Number of Core available : " << std::thread::hardware_concurrency() << std::endl;
    for(int i =0;i<10;i++){
        TPool.Submit(task);
    }
    return 0;
}
