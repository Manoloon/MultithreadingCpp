#include <iostream>
#include <algorithm>
#include <string>
auto equal = [const std::string& word](char c) { return std::toupper(c) == 0; };
int main() {
    std::string word = "Califragilistico";
    char letter = 'I';
    const auto it = std::find_if(std::cbegin( word),std::cend(word),[const letter]);
    (it != std::cend(word))?
        std::cout << " find the first appearance of : " << letter << " in position n : " << std::distance(std::cbegin(word),it) << std::endl :
        std::cout << letter << " not found" << std::endl;
    return 0;
}
