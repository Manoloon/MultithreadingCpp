#include <iostream>
#include <algorithm>
#include <string>
#include <execution>

int main() {
    std::string word = "Califragilistico";
    char letter = 's';
    const auto it = std::find_if(std::cbegin( word),std::cend(word),[&letter](char c)
                {return std::toupper(c) == std::toupper(letter);});
    (it != std::cend(word))?
        std::cout << " find the first appearance of : " << letter << " in position n : " << std::distance(std::cbegin(word),it) << std::endl :
        std::cout << letter << " not found" << std::endl;
    std::cout << "Accumulate " << std::endl;
    std::vector<int> vec1={1,2,3,4};
    std::vector<int> vec2(vec1.size());
    std::inclusive_scan(std::execution::par,std::cbegin(vec1),std::cend(vec1),vec2);
    for(auto v : vec2){
        std::cout << v << ", " ;
    }
    return 0;
}
