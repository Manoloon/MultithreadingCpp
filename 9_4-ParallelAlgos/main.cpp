#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <execution>

int main() {
    std::cout << "Accumulate " << std::endl;
    std::vector<int> vec1={0,1,2,3,4,5,6,7};

    int accu = std::accumulate(std::begin(vec1),std::end(vec1),0);
    std::cout << "Accumulate : " << accu;

    std::cout << std::endl;
    std::cout << "Inclusive_scan" << std::endl;
    std::vector<int> vecPar1={1,2,3,4};
    std::vector<int> vecPar2(vecPar1.size());
    std::inclusive_scan(std::execution::par,std::begin(vecPar1),std::end(vecPar1),std::begin(vecPar2));
    for(const auto& v : vecPar2){
        std::cout << v << ", " ;
    }
    std::cout << std::endl;
    std::cout << "Exclusive_scan" << std::endl;
    std::vector<int> vecPar3(vecPar1.size());
    std::exclusive_scan(std::execution::unseq,std::cbegin(vecPar1),std::cend(vecPar1),
        std::ostream_iterator<int>(std::cout, ", "),-1);
    std::cout << std::endl;
    return 0;
}
