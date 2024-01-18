/*
* Questions for this assignment
Are there any possible scenarios in which neither thread is able to exit the loop? If so, how could this happen?

If so, suggest a way to fix the problem.
*/

#include <thread>

int x{0};

void func() {
    while (x == 0) {
        x = 1 - x;
    }
}

int main()
{
    std::thread thr1{ func };
    std::thread thr2{ func };
	
	thr1.join();
	thr2.join();
}

