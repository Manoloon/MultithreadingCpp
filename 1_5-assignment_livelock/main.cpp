/*
* Questions for this assignment
Are there any possible scenarios in which neither thread is able to exit the loop? If so, how could this happen?
if x is written by Thr1 while , thr2 will read as x still = 0 -> so 1 - x will be 0, then x = 1 , and then , back again x = 0,
 which x = 1 should be breaking the while loop but instead keep on it, so after that it could lead to x = 1 - x (where x =1) = 0,
 infinite loop.
entering while loop : x = 0
entering while loop : x = 1
entering while loop : x = 0

If so, suggest a way to fix the problem.
 The problem is fixed by adding a mutex and creating a lock_guard just before the while loop.
 entering while loop : x = 0
*/

#include <thread>
#include <mutex>
#include <iostream>

int x{0};
std::mutex mut;
void func() {
    std::lock_guard lckguard(mut);
    while (x == 0) {
        std::cout << "entering while loop : x = " << x << std::endl;
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

