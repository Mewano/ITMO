#ifndef PLAY_HAMMURABI_INL
#define PLAY_HAMMURABI_INL

namespace play {

template<class T>
void Hammurabi(std::istream &istream, std::ostream &ostream,
              std::fstream &file, hammurabi::Game<T> &game) {
    detail::InsertGreetings(ostream);
    const auto extract_game_result = detail::ExtractGame(istream, ostream, file, game);
    if (extract_game_result == hammurabi::ser::ExtractResult::Error) {
        return;
    }

    detail::InsertGameState(ostream, game);
    bool can_play = true;
    while (can_play) {
        detail::InsertGame(file, game);
        const auto input_or = detail::ExtractRoundInput(istream, ostream, game);
        if (std::holds_alternative<detail::Exit>(input_or)) {
            break;
        }
        const auto input = std::get<hammurabi::RoundInput>(input_or);
        const auto round_result = game.PlayRound(input);
        std::visit(detail::overloaded{
            [&ostream, &can_play](hammurabi::GameOver game_over) {
                detail::InsertGameOver(ostream, game_over);
                can_play = false;
            },
            [&ostream, &game = std::as_const(game)](hammurabi::Continue) {
                detail::InsertGameState(ostream, game);
            },
            [&ostream, &game = std::as_const(game), &can_play](hammurabi::GameEnd) {
                const auto statistics = game.Statistics().value();
                detail::InsertGameState(ostream, game);
                detail::InsertGameStatistics(ostream, statistics);
                can_play = false;
            },
        }, round_result);
    }

    detail::InsertGame(file, game);
    detail::InsertGoodbye(ostream);
}

}

#endif //PLAY_HAMMURABI_INL
