//
// Created by Manoloon on 30/1/2024.
//

#ifndef INC_9_3_EXECUTIONPOLICIES_PAR_VEC_H
#define INC_9_3_EXECUTIONPOLICIES_PAR_VEC_H
namespace par_unseq{
    void run(){
        std::vector<int> vec {4,1,19,2,10,6,8,121};
        std::sort(std::execution::par_unseq,vec.begin(),vec.end(),[](int a, int b){return a<b;});
        std::cout << "************* Parallel and Vectorized ****************" << '\n';
        for(auto v : vec){
            std::cout << v << ", ";
        }
        std::cout << std::endl;
    }
}
#endif //INC_9_3_EXECUTIONPOLICIES_PAR_VEC_H
