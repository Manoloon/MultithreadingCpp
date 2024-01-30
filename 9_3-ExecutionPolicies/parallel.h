//
// Created by Manoloon on 30/1/2024.
//

#ifndef INC_9_3_EXECUTIONPOLICIES_PARALLEL_H
#define INC_9_3_EXECUTIONPOLICIES_PARALLEL_H
#include <vector>
#include <execution>

namespace par{
    void run(){
        std::vector<int> vec(20'000);
        int count =0;
        std::for_each(std::execution::par, vec.begin(), vec.end(),
                      [&count] (int& x) { x = ++count; });
        std::cout << "************* Parallel ****************" << '\n';
        for(auto v : vec){
            std::cout << v << ", ";
        }
        std::cout << std::endl;
    }
}
#endif //INC_9_3_EXECUTIONPOLICIES_PARALLEL_H
