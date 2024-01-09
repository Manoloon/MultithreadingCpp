#include <iostream>
#include <thread>
#include <string>
#include <string_view>
#include <array>

class FizzBuzz {
public:
    void operator()(std::string_view name, int n) {
        std::string result;
        if (n % 3 == 0)
            result = "Fizz";
        if (n % 5 == 0)
            result += "Buzz";
        else
            result= std::to_string(n);

        std::cout << name << " says " << result << "\n";
    }
};

int main() {
    FizzBuzz fizzBuzz;
    std::array<std::string_view, 4> childrens{"Abdul", "Bart", "Claudia", "Divya"};
    int count = 0;
    for (int i = 0; i < 10005; i++) {
        std::string_view name = childrens[count];
        if (count == childrens.size()-1) {
            count=0;
        } else {
            count++;
        }
        std::thread thr(fizzBuzz, name, i);
        thr.join();
    }
    return 0;
}
