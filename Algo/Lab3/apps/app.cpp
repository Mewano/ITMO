#include <Lab3/Sort.hpp>

#include <iostream>
#include <array>

int main() {
    std::array array = {4, 2, 7, 1, 8, 9, 0, 3, 6, 5};

    lab3::sort(array.begin(), array.end(), [](auto a, auto b) { return a < b; });

    for (auto item : array) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
}
