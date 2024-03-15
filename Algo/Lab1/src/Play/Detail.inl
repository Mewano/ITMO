#ifndef PLAY_DETAIL_INL
#define PLAY_DETAIL_INL

#include "Detail.hpp"

namespace play::detail {

void InsertGreetings(std::ostream &ostream) {
    ostream << "                                HAMMURABI\n"
               "               THE GAME ABOUT GOVERING ANCIENT SUMERIA\n\n"
               "TRY YOURSELF FOR A TEN-YEAR PERIOD\n"
               "P.s. not 10 years in game ofc\n\n";
}

void InsertNotEnoughArea(std::ostream &ostream, const hammurabi::NotEnoughArea error) {
    ostream << "HAMMURABI: THINK AGAIN. YOU OWN ONLY "
            << error.Area() << " ACRES. NOW THEN,\n";
}

void InsertNotEnoughGrain(std::ostream &ostream, const hammurabi::NotEnoughGrain error) {
    ostream << "HAMMURABI: THINK AGAIN. YOU HAVE ONLY\n"
            << error.Grain() << " BUSHELS OF GRAIN. NOW THEN,\n";
}

void InsertNotEnoughPeople(std::ostream &ostream, const hammurabi::NotEnoughPeople error) {
    ostream << "HAMURABI: THINK AGAIN. YOU HAVE ONLY "
            << error.Population() << " PEOPLE TO TEND THE FIELDS. NOW THEN,\n";
}

void InsertGameOver(std::ostream &ostream, const hammurabi::GameOver game_over) {
    ostream << game_over.DeadFromHunger() << " PEOPLE STARVED IN ONE YEAR\n"
            << "BECAUSE OF THIS SAD CIRCUMSTANCE, YOU WERE HELD RESPONSIBLE\n"
               "AND EXPIRED FROM YOUR POST\n";
}

template<class T>
void InsertGameState(std::ostream &ostream, const hammurabi::Game<T> &game) {
    ostream << "HAMURABI:  LET ME REPORT YOU THAT\n"
               "IN YEAR " << game.CurrentRound() << ",";
    if (game.DeadFromHunger() > 0) {
        ostream << " " << game.DeadFromHunger() << " PEOPLE STARVED,";
    }
    if (game.Arrived() > 0) {
        ostream << " " << game.Arrived() << " PEOPLE CAME TO THE CITY,";
    }
    ostream << "\n";

    if (game.IsPlague()) {
        ostream << "A HORRIBLE PLAGUE KILLED HALF OF YOUR PEOPLE.\n";
    }
    ostream << "POPULATION NOW IS " << game.Population() << ".\n"
            << "THE CITY NOW OWNS " << game.Area() << " ACRES.\n"
            << "YOU HARVESTED " << game.GrainFromAcre() << " BUSHELS PER ACRE.\n";
    if (game.GrainEatenByRats() > 0) {
        ostream << "RATS ATE " << game.GrainEatenByRats() << " BUSHELS.\n";
    }
    ostream << "YOU NOW HAVE " << game.Grain() << " BUSHELS IN STORE.\n"
            << "LAND IS TRADING AT " << game.AcrePrice() << " BUSHELS PER ACRE.\n";
}

void InsertGameStatistics(std::ostream &ostream, const hammurabi::Statistics statistics) {
    ostream << "DURING YOUR 10-YEAR REIGN, " << statistics.AverageDeadFromHungerPercent() << " PERCENT OF THE\n"
            << "POPULATION STARVED PER YEAR ON THE AVERAGE, I.E. A TOTAL OF\n"
            << statistics.DeadFromHunger() << " PEOPLE DIED\n"
            << "YOU STARTED WITH 10 ACRES PER PERSON AND ENDED WITH\n"
            << statistics.AreaByPerson() << " ACRES PER PERSON\n";

    const auto rank = statistics.Rank();
    switch (rank) {
        case hammurabi::Rank::D: {
            ostream << "THE PEOPLE HATE YOU! YOUR RULE WAS COMPLETELY\n"
                       "INCOMPETENT. YOU WERE EXECUTED.\n";
            break;
        }
        case hammurabi::Rank::C: {
            ostream << "YOUR PERFORMANCE WAS BAD. NOT ENOUGH TO EXECUTE YOU,\n"
                       "BUT ENOUGH TO FIRE YOU\n";
            break;
        }
        case hammurabi::Rank::B: {
            ostream << "YOUR PERFORMANCE COULD HAVE BEEN BETTER, BUT\n"
                       "REALLY WASN'T TOO BAD AT ALL. PEOPLE\n";
            break;
        }
        case hammurabi::Rank::A: {
            ostream << "SUCH A FANTASTIC PERFORMANCE! THE PERIOD OF YOUR RULE\n"
                       "WILL BE CALLED THE GOLDEN AGE OF ANCIENT SUMERIA\n";
            break;
        }
    }
}

void InsertGoodbye(std::ostream &ostream) {
    ostream << "\nGOODBYE FOR NOW.\n";
}

void InsertOldGameFound(std::ostream &ostream) {
    ostream << "HAMURABI:  I FOUND SOME ARCHIVES OF YOUR RULE!\n";
}

constexpr hammurabi::string_literal kExitCommand = "exit";

constexpr bool CanExit(const std::string_view string) noexcept {
    return hammurabi::detail::Trim(string) == kExitCommand;
}

template<std::unsigned_integral T>
ExitOr<T> ExtractUnsigned(std::istream &istream, std::ostream &ostream, const std::string_view message) {
    const auto error_message = "HAMURABI: I DO NOT UNDERSTAND YOU. PLEASE REPEAT MORE CLEARLY\n";
    std::make_signed_t<T> value;
    std::string buffer;

    while (true) {
        // prints message
        ostream << message;
        // gets new line and check for exit
        std::getline(istream, buffer);
        if (CanExit(buffer)) {
            return Exit{};
        }
        // converts input into integer
        try {
            value = std::stoll(buffer);
        } catch (const std::logic_error &) {
            ostream << error_message;
            continue;
        }
        // checks for negative values
        if (value < 0) {
            ostream << error_message;
            continue;
        }
        return static_cast<T>(value);
    }
}

template<class... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template<class T>
ExitOr<hammurabi::AreaToBuy> ExtractAreaToBuy(std::istream &istream, std::ostream &ostream,
                                             const hammurabi::Game<T> &game) {
    ExitOr<hammurabi::Acres> input;
    std::optional<hammurabi::AreaToBuyResult> result;
    bool try_again = true;
    while (try_again) {
        input = ExtractUnsigned<hammurabi::Acres>(
            istream, ostream, "HOW MANY ACRES DO YOU WISH TO BUY? ");
        if (std::holds_alternative<Exit>(input)) {
            return Exit{};
        }
        const auto area_to_buy = std::get<hammurabi::Acres>(input);
        result = hammurabi::AreaToBuy::New(area_to_buy, game);
        std::visit(detail::overloaded{
            [&try_again](hammurabi::AreaToBuy) { try_again = false; },
            [&ostream](hammurabi::NotEnoughGrain error) { InsertNotEnoughGrain(ostream, error); },
        }, result.value());
    }
    return std::get<hammurabi::AreaToBuy>(result.value());
}

template<class T>
ExitOr<hammurabi::AreaToSell> ExtractAreaToSell(std::istream &istream, std::ostream &ostream,
                                               const hammurabi::Game<T> &game) {
    ExitOr<hammurabi::Acres> input;
    std::optional<hammurabi::AreaToSellResult> result;
    bool try_again = true;
    while (try_again) {
        input = ExtractUnsigned<hammurabi::Acres>(
            istream, ostream, "HOW MANY ACRES DO YOU WISH TO SELL? ");
        if (std::holds_alternative<Exit>(input)) {
            return Exit{};
        }
        const auto area_to_sell = std::get<hammurabi::Acres>(input);
        result = hammurabi::AreaToSell::New(area_to_sell, game);
        std::visit(detail::overloaded{
            [&try_again](hammurabi::AreaToSell) { try_again = false; },
            [&ostream](hammurabi::NotEnoughArea error) { InsertNotEnoughArea(ostream, error); },
        }, result.value());
    }
    return std::get<hammurabi::AreaToSell>(result.value());
}

template<class T>
ExitOr<hammurabi::GrainToFeed> ExtractGrainToFeed(std::istream &istream, std::ostream &ostream,
                                                 const hammurabi::Game<T> &game) {
    ExitOr<hammurabi::Bushels> input;
    std::optional<hammurabi::GrainToFeedResult> result;
    bool try_again = true;
    while (try_again) {
        input = ExtractUnsigned<hammurabi::Bushels>(
            istream, ostream, "HOW MANY BUSHELS DO YOU WISH TO FEED YOUR PEOPLE? ");
        if (std::holds_alternative<Exit>(input)) {
            return Exit{};
        }
        const auto grain_to_feed = std::get<hammurabi::Bushels>(input);
        result = hammurabi::GrainToFeed::New(grain_to_feed, game);
        std::visit(detail::overloaded{
            [&try_again](hamurabi::GrainToFeed) { try_again = false; },
            [&ostream](hamurabi::NotEnoughGrain error) { InsertNotEnoughGrain(ostream, error); },
        }, result.value());
    }
    return std::get<hammurabi::GrainToFeed>(result.value());
}

template<class T>
ExitOr<hammurabi::AreaToPlant> ExtractAreaToPlant(std::istream &istream, std::ostream &ostream,
                                                 const hammurabi::Game<T> &game) {
    ExitOr<hammurabi::Acres> input;
    std::optional<hammurabi::AreaToPlantResult> result;
    bool try_again = true;
    while (try_again) {
        input = ExtractUnsigned<hammurabi::Acres>(
            istream, ostream, "HOW MANY ACRES DO YOU WISH TO PLANT WITH SEED? ");
        if (std::holds_alternative<Exit>(input)) {
            return Exit{};
        }
        const auto area_to_plant = std::get<hammurabi::Acres>(input);
        result = hammurabi::AreaToPlant::New(area_to_plant, game);
        std::visit(detail::overloaded{
            [&try_again](hamurabi::AreaToPlant) { try_again = false; },
            [&ostream](hammurabi::NotEnoughArea error) { InsertNotEnoughArea(ostream, error); },
            [&ostream](hammurabi::NotEnoughGrain error) { InsertNotEnoughGrain(ostream, error); },
            [&ostream](hammurabi::NotEnoughPeople error) { InsertNotEnoughPeople(ostream, error); },
        }, result.value());
    }
    return std::get<hammurabi::AreaToPlant>(result.value());
}

template<class T>
ExitOr<hammurabi::RoundInput> ExtractRoundInput(std::istream &istream, std::ostream &ostream,
                                               const hammurabi::Game<T> &game) {
    std::optional<hammurabi::RoundInputResult> result;
    bool try_again = true;
    while (try_again) {
        const auto area_to_buy_or = ExtractAreaToBuy(istream, ostream, game);
        if (std::holds_alternative<Exit>(area_to_buy_or)) {
            return Exit{};
        }
        const auto area_to_buy = std::get<hammurabi::AreaToBuy>(area_to_buy_or);
        
        const auto area_to_sell_or = ExtractAreaToSell(istream, ostream, game);
        if (std::holds_alternative<Exit>(area_to_sell_or)) {
            return Exit{};
        }
        const auto area_to_sell = std::get<hammurabi::AreaToSell>(area_to_sell_or);
        
        const auto grain_to_feed_or = ExtractGrainToFeed(istream, ostream, game);
        if (std::holds_alternative<Exit>(grain_to_feed_or)) {
            return Exit{};
        }
        const auto grain_to_feed = std::get<hammurabi::GrainToFeed>(grain_to_feed_or);
        
        const auto area_to_plant_or = ExtractAreaToPlant(istream, ostream, game);
        if (std::holds_alternative<Exit>(area_to_plant_or)) {
            return Exit{};
        }
        const auto area_to_plant = std::get<hammurabi::AreaToPlant>(area_to_plant_or);
        // checks for round input result
        result = hammurabi::RoundInput::New(area_to_buy, area_to_sell, grain_to_feed, area_to_plant, game);
        std::visit(detail::overloaded{
            [&try_again](hammurabi::RoundInput) { try_again = false; },
            [&ostream](hammurabi::NotEnoughArea error) { InsertNotEnoughArea(ostream, error); },
            [&ostream](hammurabi::NotEnoughGrain error) { InsertNotEnoughGrain(ostream, error); },
            [&ostream](hammurabi::NotEnoughPeople error) { InsertNotEnoughPeople(ostream, error); },
        }, result.value());
    }
    ostream << "\n";
    return std::get<hammurabi::RoundInput>(result.value());
}

constexpr hammurabi::string_literal kSaveFileName = "game.yaml";

template<class T>
void InsertGame(std::fstream &file, const hammurabi::Game<T> &game) {
    file.open(kSaveFileName, std::fstream::out | std::fstream::trunc);
    hammurabi::ser::InsertGame(file, game, hammurabi::ser::Format::YAML);
    file.close();
}

template<class T>
hammurabi::ser::ExtractResult ExtractGame(std::istream &istream, std::ostream &ostream,
                                         std::fstream &file, hammurabi::Game<T> &game) {
    namespace ser = hammurabi::serialization;

    file.open(kSaveFileName, std::fstream::in);
    if (!file.is_open()) {
        file.clear();
        return ser::ExtractResult::Success;
    }
    InsertOldGameFound(ostream);
    const auto continue_or_start_new = ExtractContinueOrStartNew(istream, ostream);
    switch (continue_or_start_new) {
        case ContinueOrStartNew::StartNew: {
            file.close();
            return ser::ExtractResult::Success;
        }
        case ContinueOrStartNew::Continue: {
            break;
        }
    }
    const auto extract_result = ser::ExtractGame(file, game, ser::Format::YAML);
    file.close();
    return extract_result;
}

constexpr hammurabi::string_literal kContinueCommand = "continue";

constexpr bool CanContinue(std::string_view string) noexcept {
    return hammurabi::detail::Trim(string) == kContinueCommand;
}

constexpr hammurabi::string_literal kStartNewCommand = "new";

constexpr bool CanStartNew(std::string_view string) noexcept {
    return hammurabi::detail::Trim(string) == kStartNewCommand;
}

[[nodiscard]]
ContinueOrStartNew ExtractContinueOrStartNew(std::istream &istream, std::ostream &ostream) {
    constexpr auto message = "SHALL WE CONTINUE? OR MAYBE START WITH A CLEAN NEW PAPER? ";
    constexpr auto error_message = "HAMURABI: I DO NOT UNDERSTAND YOU. PLEASE REPEAT MORE CLEARLY\n";
    std::string buffer;

    while (true) {
        ostream << message;
        std::getline(istream, buffer);
        if (CanContinue(buffer)) {
            return ContinueOrStartNew::Continue;
        }
        if (CanStartNew(buffer)) {
            return ContinueOrStartNew::StartNew;
        }
        ostream << error_message;
    }
}

}

#endif //PLAY_DETAIL_INL
