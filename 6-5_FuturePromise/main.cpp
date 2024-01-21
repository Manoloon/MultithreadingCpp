#include <iostream>
#include<thread>
#include<future>
using namespace std::chrono_literals;
std::mutex print_mut;
void produce(std::promise<int>& px,int n){
    std::cout << "Producer want this number times 2 : " << n << std::endl;
    int x =2*n;
    std::this_thread::sleep_for(2s);
    std::cout << "Promise sets shared state value to :" << x << std::endl;
    px.set_value(x);
}
void consume(std::shared_future<int>& fx){
    std::unique_lock print_lck(print_mut);
    std::cout << "Consumer Thread :" << std::this_thread::get_id() << std::endl;
    std::cout << "Future calling get()... " << std::endl;
    int x = fx.get();
    std::cout << " future returns from calling get().." << std::endl;
    std::cout << "The result is : " << x << std::endl;
}
int main() {
    std::promise<int> prom;
    std::shared_future<int> fut = prom.get_future();
    std::thread thr_producer(produce,std::ref(prom),2);

    std::thread thr_consumer(consume,std::ref(fut));
    std::thread thr_consumer2(consume,std::ref(fut));

    thr_producer.join();
    thr_consumer.join();
    thr_consumer2.join();
    return 0;
}
