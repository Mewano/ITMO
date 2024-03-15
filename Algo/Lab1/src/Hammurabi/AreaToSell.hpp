#ifndef HAMMURABI_AREA_TO_SELL
#define HAMMURABI_AREA_TO_SELL

#include <variant>

#include "NotEnoughArea.hpp"

namespace hammurabi {

class AreaToSell;
using AreaToSellResult = std::variant<AreaToSell, NotEnoughArea>;

class AreaToSell final {
  public:
    template<class T>
    constexpr static AreaToSellResult New(Acres area_to_sell, const Game<T> &game) noexcept;

    constexpr explicit operator Acres() const noexcept;

  private:
    constexpr explicit AreaToSell(Acres area_to_sell) noexcept;

    Acres area_to_sell_;
};

}

#include "AreaToSell.inl"

#endif //HAMMURABI_AREA_TO_SELL
