#ifndef HAMMURABI_GRAIN_TO_FEED
#define HAMMURABI_GRAIN_TO_FEED

#include <variant>

#include "NotEnoughGrain.hpp"

namespace hammurabi {

class GrainToFeed;
using GrainToFeedResult = std::variant<GrainToFeed, NotEnoughGrain>;

class GrainToFeed final {
  public:
    template<class T>
    constexpr static GrainToFeedResult New(Bushels grain_to_feed, const Game<T> &game) noexcept;

    constexpr explicit operator Bushels() const noexcept;

  private:
    constexpr explicit GrainToFeed(Bushels grain_to_feed) noexcept;

    Bushels grain_to_feed_;
};

}

#include "GrainToFeed.inl"

#endif //HAMMURABI_GRAIN_TO_FEED
