#include <string>
#include <iostream>

int main() {
    std::string s;
    std::getline(std::cin, s);

    bool seen[26] = {false};
    int counter = 0;

    for (char c : s){
        if (c == ' ') continue;
        int idx = c - 'a';
        if (!seen[idx]){
            seen[idx] = true;
            counter++;
        }
    }
    std::cout << counter << std::endl;

    return  0;
}