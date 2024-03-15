#ifndef HAMMURABI_AREA_TO_BUY
#define HAMMURABI_AREA_TO_BUY

#include <variant>

#include "NotEnoughGrain.hpp"

namespace hammurabi {

class AreaToBuy;
using AreaToBuyResult = std::variant<AreaToBuy, NotEnoughGrain>;

class AreaToBuy final {
  public:
    template<class T>
    constexpr static AreaToBuyResult New(Acres area_to_buy, const Game<T> &game) noexcept;

    constexpr explicit operator Acres() const noexcept;

  private:
    constexpr explicit AreaToBuy(Acres area_to_buy) noexcept;

    Acres area_to_buy_;
};

}

#include "AreaToBuy.inl"

#endif //HAMMURABI_AREA_TO_BUY
