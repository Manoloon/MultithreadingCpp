#include <iostream>
#include <thread>
#include <future>

using namespace std::chrono_literals;

int task(){
    std::cout << "Execute task id " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Returning from task()\n";
    return 666;
}
void func(const std::string& option = "default") {
    std::future<int> resultFut;
    if (option == "async")
            resultFut = std::async(std::launch::async,task);
    else if (option == "deferred")
            resultFut = std::async(std::launch::deferred,task);
    else
            resultFut = std::async(task);
    std::cout << "Calling async with option \"" << option << "\"\n";
    std::this_thread::sleep_for(2s);
    std::cout << "Calling Get()\n";
    std::cout << "Task result : " << resultFut.get() << '\n';
}
int main() {
    std::cout << "in main with id : " << std::this_thread::get_id() << '\n';
    func("async");
    func("deferred");
    func();
    return 0;
}
