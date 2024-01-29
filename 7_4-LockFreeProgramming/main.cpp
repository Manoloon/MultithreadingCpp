//lock-free queue class
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <list>

template<typename T>
struct LockFreeQueue {
private:
    std::list<T> list;
    typename std::list<T>::iterator iHead;
    typename std::list<T>::iterator iTail;
public:
    LockFreeQueue() {
        // we add a dummy element to the list
        list.push_back(T());
        // so head its an element
        iHead = std::begin(list);
        // and tail is another different
        iTail = std::end(list);
    }

    void Produce(const T &t) {
        list.push_back(t);
        iTail = std::end(list);
        list.erase(std::begin(list), iHead);
    }

    bool Consume(T &t) {
        auto iFirst = iHead;
        ++iFirst;
        if (iFirst != iTail) {
            iHead = iFirst;
            t = *iHead; // fetch first element
            return true;
        }
        return false; // no first element
    }

    void Print() {
        auto head = iHead;
        ++head;
        for (auto item = head; item != iTail; ++item) {
            std::cout <<" element :" << *item << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    LockFreeQueue<int> lfq;
    std::vector<std::thread> threads;
    int j = 1;
    for (int i = 0; i < 10; i++) {
        std::thread producer(&LockFreeQueue<int>::Produce, &lfq, std::ref(i));
        threads.push_back(std::move(producer));
        std::thread consumer(&LockFreeQueue<int>::Consume, &lfq, std::ref(j));
        threads.push_back(std::move(consumer));
    }
    for (auto &t: threads) {
        t.join();
    }
    lfq.Print();
}