//
// Created by Manoloon on 2/2/2024.
//

#ifndef CONCURRENTQUEUE_H
#define CONCURRENTQUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

class concurrentQueue_exception : public std::runtime_error{
public:
    concurrentQueue_exception() : std::runtime_error("Queue is empty"){}
    concurrentQueue_exception(const char *c) : std::runtime_error(c){}
};
template<class T>
class concurrentQueue{
    std::mutex mut;
    std::queue<T> queue;
    std::condition_variable cv;
public:
    concurrentQueue()=default;
    void push(T value) {
        std::lock_guard<std::mutex> lck(mut);
        queue.push(value);
        cv.notify_one();
    }
    void pop(T& value) {
        std::unique_lock<std::mutex> lck(mut);
        cv.wait(lck,[this]{return !queue.empty();});
        value = queue.front();
        queue.pop();
    }
};
#endif //CONCURRENTQUEUE_H
