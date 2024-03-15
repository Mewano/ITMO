#ifndef PLAY_DETAIL
#define PLAY_DETAIL

#include "../Hammurabi/Game.hpp"

#include <fstream>

namespace play::detail {

static inline void InsertGreetings(std::ostream &ostream);

static inline void InsertNotEnoughArea(std::ostream &ostream, hammurabi::NotEnoughArea error);

static inline void InsertNotEnoughGrain(std::ostream &ostream, hammurabi::NotEnoughGrain error);

static inline void InsertNotEnoughPeople(std::ostream &ostream, hammurabi::NotEnoughPeople error);

static inline void InsertGameOver(std::ostream &ostream, hammurabi::GameOver game_over);

template<class T>
static inline void InsertGameState(std::ostream &ostream, const hammurabi::Game<T> &game);

static inline void InsertGameStatistics(std::ostream &ostream, hammurabi::Statistics statistics);

static inline void InsertGoodbye(std::ostream &ostream);

static inline void InsertOldGameFound(std::ostream &ostream);

extern const hammurabi::string_literal kExitCommand;

static inline constexpr bool CanExit(std::string_view string) noexcept;

struct Exit final {};

template<class T>
using ExitOr = std::variant<Exit, T>;

template<std::unsigned_integral T>
[[nodiscard]]
static inline ExitOr<T> ExtractUnsigned(std::istream &istream, std::ostream &ostream,
                                        std::string_view message);

template<class T>
[[nodiscard]]
static inline ExitOr<hammurabi::AreaToBuy> ExtractAreaToBuy(std::istream &istream, std::ostream &ostream,
                                                           const hammurabi::Game<T> &game);

template<class T>
[[nodiscard]]
static inline ExitOr<hammurabi::AreaToSell> ExtractAreaToSell(std::istream &istream, std::ostream &ostream,
                                                             const hammurabi::Game<T> &game);

template<class T>
[[nodiscard]]
static inline ExitOr<hammurabi::GrainToFeed> ExtractGrainToFeed(std::istream &istream, std::ostream &ostream,
                                                               const hammurabi::Game<T> &game);

template<class T>
[[nodiscard]]
static inline ExitOr<hammurabi::AreaToPlant> ExtractAreaToPlant(std::istream &istream, std::ostream &ostream,
                                                               const hammurabi::Game<T> &game);

template<class T>
[[nodiscard]]
static inline ExitOr<hammurabi::RoundInput> ExtractRoundInput(std::istream &istream, std::ostream &ostream,
                                                             const hammurabi::Game<T> &game);

extern const hammurabi::string_literal kSaveFileName;

template<class T>
static inline void InsertGame(std::fstream &file, const hammurabi::Game<T> &game);

template<class T>
[[nodiscard]]
static inline hammurabi::ser::ExtractResult ExtractGame(std::istream &istream, std::ostream &ostream,
                                                       std::fstream &file, hammurabi::Game<T> &game);

enum class ContinueOrStartNew {
    Continue,
    StartNew,
};

extern const hammurabi::string_literal kContinueCommand;

static inline constexpr bool CanContinue(std::string_view string) noexcept;

extern const hammurabi::string_literal kStartNewCommand;

static inline constexpr bool CanStartNew(std::string_view string) noexcept;

[[nodiscard]]
static inline ContinueOrStartNew ExtractContinueOrStartNew(std::istream &istream, std::ostream &ostream);

}

#include "Detail.inl"

#endif //PLAY_DETAIL
