#include <iostream>

#include "Play/Hammurabi.hpp"

int main() {
    std::random_device random_device{};
    std::mt19937_64 generator{random_device()};
    hammurabi::Game game{generator};
    std::fstream file{};
    play::Hammurabi(std::cin, std::cout, file, game);
    return 0;
}
