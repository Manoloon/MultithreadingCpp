#include <future>
#include <iostream>
#include <string>
#include "concurrentQueue.h"

using namespace std::chrono_literals;

concurrentQueue<std::string> q;
void writer() {
    std::cout << "writer call " << '\n';
    q.push("HOLA");
    std::cout << "writer ends " << '\n';
}
void reader() {
    std::string val;
    std::cout << "Reader call " << '\n';

    q.pop(val);
    std::cout << "Reader get " << val << '\n';
    std::cout << "Reader ends " << '\n';
}
int main() {
    auto wrt = std::async (std::launch::async,writer);
    auto rdr = std::async (std::launch::async,reader);
    wrt.wait();
    rdr.wait();
    return 0;
}
