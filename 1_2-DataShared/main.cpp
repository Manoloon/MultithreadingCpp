//
// Created by Manoloon on 9/1/2024.
//

#include <thread>
#include <iostream>
#include <vector>
static int number=0;
std::mutex mutex_sum;
void Sum(){
    // 10 * 10000 = 100000 ;-)
    for(int i=0;i<10000;i++){
        std::lock_guard<std::mutex> guard(mutex_sum);
        number++;
    }
}

int main(){
    std::vector<std::thread> threads;

    for(int i = 0; i< 10 ; i++){
        threads.emplace_back(Sum);
    }
    for(std::thread& t : threads){
        t.join();
    }
    std::cout << number;
}