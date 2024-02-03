#include <vector>
#include <functional>
#include <atomic>
#include <thread>
#include "concurrentQueue.h"

using func = std::function<void()>;

class threadsPool{
    concurrentQueue<func> queue;
    std::vector<std::thread> threads;
    void Worker(){
        while (true)
        {
            func task;
            queue.pop(task);
            task();
        }
    }
    public:
    threadsPool(){
        const unsigned threadCount = std::thread::hardware_concurrency();
        for(unsigned i = 0;i<threadCount;i++){
            threads.emplace_back(std::thread{&threadsPool::Worker,this});
        }
    }
    ~threadsPool(){
        for(auto& t : threads){
            t.join();
        }
    }
    void Submit(func function){
        queue.push(function);
    }
};