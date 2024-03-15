#ifndef PLAY_HAMMURABI
#define PLAY_HAMMURABI

#include "Detail.hpp"

namespace play {

template<class T>
void Hammurabi(std::istream &istream, std::ostream &ostream,
              std::fstream &file, hammurabi::Game<T> &game);

}

#include "Hammurabi.inl"

#endif //PLAY_HAMMURABI
