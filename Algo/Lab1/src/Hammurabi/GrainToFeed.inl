#ifndef HAMMURABI_GRAIN_TO_FEED_INL
#define HAMMURABI_GRAIN_TO_FEED_INL

namespace hammurabi {

template<class T>
constexpr GrainToFeedResult GrainToFeed::New(const Bushels grain_to_feed, const Game<T> &game) noexcept {
    const auto grain = game.Grain();
    if (grain_to_feed > grain) {
        return NotEnoughGrain{game};
    }
    return GrainToFeed{grain_to_feed};
}

constexpr GrainToFeed::operator Bushels() const noexcept {
    return grain_to_feed_;
}

constexpr GrainToFeed::GrainToFeed(const Bushels grain_to_feed) noexcept
    : grain_to_feed_{grain_to_feed} {}

}

#endif //HAMMURABI_GRAIN_TO_FEED_INL
