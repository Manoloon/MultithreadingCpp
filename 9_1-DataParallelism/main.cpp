//lock-free queue class
#include <vector>
#include <iostream>
#include <thread>
#include <future>
#include <random>
#include <algorithm>
#include <numeric>
#include "accumAsync.h"
#include "accumPackagedTask.h"

static std::mt19937 mt;
std::uniform_real_distribution<double> dist(0,100);

int main() {
    std::vector<double> vec(16);
    std::iota(std::begin(vec),std::end(vec),1.0);

    std::vector<double> vecRand(10000);
    std::generate(std::begin(vecRand),std::end(vecRand),[&vecRand](){return dist(mt);});
    std::cout << "Using Async : sum the first 16 integers :" << asyncAccum::add_parallel(vec) << std::endl;
    std::cout << "Using Async : sum 10000 random nums :" << asyncAccum::add_parallel(vecRand) << std::endl;

    std::cout << "Using Packaged_task : sum the first 16 integers :" << accumPackagedTask::add_parallel(vec) << std::endl;
    std::cout << "Using Packaged_task : sum 10000 random nums :" << accumPackagedTask::add_parallel(vecRand) << std::endl;
    return 0;
}