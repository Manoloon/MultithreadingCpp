#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string word = "Califragilistico";
    char letter = 's';
    const auto it = std::find_if(std::cbegin( word),std::cend(word),[&letter](char c)
                {return std::toupper(c) == std::toupper(letter);});
    (it != std::cend(word))?
        std::cout << " find the first appearance of : " << letter << " in position n : " << std::distance(std::cbegin(word),it) << std::endl :
        std::cout << letter << " not found" << std::endl;
    return 0;
}
