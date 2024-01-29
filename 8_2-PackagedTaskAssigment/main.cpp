//lock-free queue class
#include <vector>
#include <iostream>
#include <thread>
#include <future>

using namespace std::chrono_literals;
std::mutex print_mut;
void ProduceSum(std::promise<int>& sum,int a,int b){
    int result = a + b;
    std::this_thread::sleep_for(2s);
    sum.set_value(result);
}
void ConsumeSum(std::shared_future<int>& fSum){
    std::unique_lock print_lck(print_mut);
    std::cout << "Waiting for future: " << std::endl;
    int sum = fSum.get();
    std::cout << "Future sum is here : " << sum << std::endl;
}
int main() {
    std::promise<int> promise;
    std::shared_future<int> fut = promise.get_future();

    std::thread thrProd(ProduceSum,std::ref(promise),2,3);

    std::thread thrCons(ConsumeSum,std::ref(fut));
    thrProd.join();
    thrCons.join();

    return 0;
}