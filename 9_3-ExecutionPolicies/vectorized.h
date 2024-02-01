//
// Created by Manoloon on 30/1/2024.
//

#ifndef INC_9_3_EXECUTIONPOLICIES_VECTORIZED_H
#define INC_9_3_EXECUTIONPOLICIES_VECTORIZED_H
#include <numeric>
namespace unseq{
    void run(){
        std::vector<int> vec={1,2,3,4,5,6};
        std::vector<int> count(vec.size());
        std::inclusive_scan(std::execution::unseq, vec.cbegin(), vec.cend(),count.begin());
        std::cout << "************* Vectorized ****************" << '\n';
        for(auto c : count){
            std::cout << c << ", ";
        }
        std::cout << std::endl;
    }
    void runAndFail(){
        std::vector<int> vec(20'000);
        int count =0;
        try{
            std::for_each(std::execution::unseq, vec.begin(), vec.end(),
                          [&count] (int& x) { throw std::out_of_range("Out of range"); });
        }
        catch (std::exception& e){
            std::cout << "************* Parallel Exception ****************" << '\n';
            std::cout << "Exception caught : " << e.what() << std::endl;
        }
    }
}
#endif //INC_9_3_EXECUTIONPOLICIES_VECTORIZED_H
