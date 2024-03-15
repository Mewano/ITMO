#ifndef HAMMURABI_ROUND_INPUT
#define HAMMURABI_ROUND_INPUT

#include <variant>

#include "AreaToBuy.hpp"
#include "AreaToSell.hpp"
#include "GrainToFeed.hpp"
#include "AreaToPlant.hpp"

namespace hammurabi {

class RoundInput;
using RoundInputResult = std::variant<RoundInput, NotEnoughArea, NotEnoughGrain, NotEnoughPeople>;

class RoundInput final {
  public:
    template<class T>
    constexpr static RoundInputResult New(AreaToBuy area_to_buy,
                                          AreaToSell area_to_sell,
                                          GrainToFeed grain_to_feed,
                                          AreaToPlant area_to_plant,
                                          const Game<T> &game) noexcept;

    [[nodiscard]]
    constexpr AreaToBuy AreaToBuy() const;

    [[nodiscard]]
    constexpr AreaToSell AreaToSell() const;

    [[nodiscard]]
    constexpr GrainToFeed GrainToFeed() const;

    [[nodiscard]]
    constexpr AreaToPlant AreaToPlant() const;

  private:
    constexpr explicit RoundInput(hammurabi::AreaToBuy area_to_buy,
                                  hammurabi::AreaToSell area_to_sell,
                                  hammurabi::GrainToFeed grain_to_feed,
                                  hammurabi::AreaToPlant area_to_plant) noexcept;

    hammurabi::AreaToBuy area_to_buy_;
    hammurabi::AreaToSell area_to_sell_;
    hammurabi::GrainToFeed grain_to_feed_;
    hammurabi::AreaToPlant area_to_plant_;
};

}

#include "RoundInput.inl"

#endif //HAMMURABI_ROUND_INPUT
