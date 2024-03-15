#ifndef HAMMURABI_NOT_ENOUGH_AREA_INL
#define HAMMURABI_NOT_ENOUGH_AREA_INL

namespace hammurabi {

template<class T>
constexpr NotEnoughArea::NotEnoughArea(const Game<T> &game) noexcept
    : area_{game.Area()} {}

constexpr Acres NotEnoughArea::Area() const noexcept {
    return area_;
}

}

#endif //HAMMURABI_NOT_ENOUGH_AREA_INL
