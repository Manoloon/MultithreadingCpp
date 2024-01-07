#include <iostream>
#include <thread>
#include <iostream>
#include <string>
#include <vector>

class FizzBuzz {
public:
    void operator()(std::string name,int n){
        std::string result;
        if (n %3 == 0)
            result = "Fizz";
        if (n % 5 == 0)
            result += "Buzz";
        std::cout << name << " says " << result << "\n";
    }
};

int main() {
    FizzBuzz fizzBuzz;
    std::vector<std::string> childs{"Abdul","Bart","Claudia","Divya"};

    for(int i = 1;i < 5;i++){
        std::thread thr1(fizzBuzz,childs[i],i);
        thr1.join();
    }

    return 0;
}
