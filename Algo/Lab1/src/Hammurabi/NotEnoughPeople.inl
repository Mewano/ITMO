#ifndef HAMMURABI_NOT_ENOUGH_PEOPLE_INL
#define HAMMURABI_NOT_ENOUGH_PEOPLE_INL

namespace hammurabi {

template<class T>
constexpr NotEnoughPeople::NotEnoughPeople(const Game<T> &game) noexcept
    : population_{game.Population()} {}

constexpr People NotEnoughPeople::Population() const noexcept {
    return population_;
}

}

#endif //HAMMURABI_NOT_ENOUGH_PEOPLE_INL
