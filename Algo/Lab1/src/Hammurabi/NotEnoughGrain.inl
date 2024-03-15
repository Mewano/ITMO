#ifndef HAMMURABI_NOT_ENOUGH_GRAIN_INL
#define HAMMURABI_NOT_ENOUGH_GRAIN_INL

namespace hammurabi {

template<class T>
constexpr NotEnoughGrain::NotEnoughGrain(const Game<T> &game) noexcept
    : grain_{game.Grain()} {}

constexpr Bushels NotEnoughGrain::Grain() const noexcept {
    return grain_;
}

}

#endif //HAMMURABI_NOT_ENOUGH_GRAIN_INL
