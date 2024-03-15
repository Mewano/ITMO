#ifndef HAMMURABI_NOT_ENOUGH_PEOPLE
#define HAMMURABI_NOT_ENOUGH_PEOPLE

#include "Resources.hpp"
#include "Game.fwd"

namespace hammurabi {

class NotEnoughPeople final {
  public:
    template<class T>
    constexpr explicit NotEnoughPeople(const Game<T> &game) noexcept;

    [[nodiscard]]
    constexpr People Population() const noexcept;

  private:
    People population_;
};

}

#include "NotEnoughPeople.inl"

#endif //HAMMURABI_NOT_ENOUGH_PEOPLE
