#include <iostream>
#include<thread>
#include<future>
using namespace std::chrono_literals;

void produce(std::promise<int>& px){
    int x =32;
    std::this_thread::sleep_for(2s);
    std::cout << "Promise sets shared state to :" << x << std::endl;
    px.set_value(x);
}
void consume(std::future<int>& fx){
    std::cout << "Future calling get()..." << std::endl;
    int x = fx.get();
    std::cout << " future returns from calling get().." << std::endl;
    std::cout << "The result is : " << x << std::endl;
}
int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread thr_producer(produce,std::ref(prom));
    std::thread thr_consumer(consume,std::ref(fut));
    thr_producer.join();
    thr_consumer.join();
    return 0;
}
