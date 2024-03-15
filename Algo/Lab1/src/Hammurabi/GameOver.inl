#ifndef HAMMURABI_GAME_OVER_INL
#define HAMMURABI_GAME_OVER_INL

namespace hammurabi {

template<class T>
constexpr GameOver::GameOver(const Game<T> &game) noexcept
    : dead_from_hunger_{game.DeadFromHunger()} {}

constexpr People GameOver::DeadFromHunger() const noexcept {
    return dead_from_hunger_;
}

}

#endif //HAMMURABI_GAME_OVER_INL
