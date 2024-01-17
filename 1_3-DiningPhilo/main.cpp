#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <array>
#include <vector>

using namespace std::chrono_literals;

constexpr int nFork = 5;
constexpr int nPhilosopher = 5;
const std::array<std::string,5> names={ "A","B","C","D","E"};
std::array<int,5> mouthfuls;
constexpr auto think_time = 2s;
constexpr auto eat_time = 1s;
std::array<std::mutex,5> fork_mutex;
std::mutex print_mutex;

// Iterate forks
void print(int n,const std::string& str, int n_Fork) {
    std::lock_guard print_lck(print_mutex);
    std::cout << "Philosopher " << names[n] << str << n_Fork << std::endl;
}
// Philosopher states
void print(int n, const std::string& str){
    std::lock_guard print_lck(print_mutex);
    std::cout << "Philosopher " << names[n] << str << std::endl;
}

void dine(int nPhilo){
    int lFork = nPhilo;
    int rFork = (nPhilo+1) % nFork;
    print(nPhilo,"Left Fork is : ", lFork);
    print(nPhilo, "Right Fork is : ", rFork);
    print(nPhilo," is Thinking...");

    std::this_thread::sleep_for(think_time);

    print(nPhilo," reaches for Fork : ", lFork);
    fork_mutex[lFork].lock();

    print(nPhilo, " pick up fork : ", lFork);
    print(nPhilo," is Thinking...");

    std::this_thread::sleep_for(think_time);
    fork_mutex[rFork].lock();

    print(nPhilo, " pick up fork : ", rFork);
    print(nPhilo," is eating...");
    std::this_thread::sleep_for(eat_time);

    print(nPhilo, " puts down the fork : ", lFork);
    print(nPhilo, " puts down the fork : ", rFork);
    print (nPhilo, " is thinking...");

    fork_mutex[lFork].unlock();
    fork_mutex[rFork].unlock();
    std::this_thread::sleep_for(think_time);
}
int main() {
    std::vector<std::thread> threads;
    threads.reserve(5);
    for(int i = 0; i < nPhilosopher; i++){
        threads.push_back(std::move(std::thread{dine,i}));
    }
    for(std::thread& t : threads){
        t.join();
    }

    for(int i = 0; i < nPhilosopher; i++){
        std::cout << " Philosopher : " << names[i] << std::endl;
        std::cout << " had : " << mouthfuls[i] << std::endl;
    }
    return 0;
}
