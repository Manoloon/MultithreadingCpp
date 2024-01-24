#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> x =0;
    int y = 10;
    std::cout << "load x :" << x.load() << std::endl;
    x.store(y);
    std::cout << "x after store y :" << x << std::endl;
    std::cout << "x = y * 2 :" << (x = y * 2) << std::endl;

    std::cout << "x before exchange y :" << x << std::endl;
    std::cout << "x exchange y :" << x.exchange(y) << std::endl;
    std::cout << "x after exchange y :" << x << std::endl;
    return 0;
}
