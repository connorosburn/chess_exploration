#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP
#include "../Game.hpp"
#include <vector>
#include "../../json.hpp"

const int tttBoardSize {3};

const std::vector<std::vector<Player>> defaultTicTacToeBoard(tttBoardSize, std::vector<Player>(tttBoardSize, Player::Null));

class TicTacToe : public Game {
    public:
        TicTacToe();
        TicTacToe(std::string snapshot);
        double getScore(Player player);
        std::vector<Game*> everyHypotheticalGame();
        bool over();
        int getTurnCount();
        std::string getSnapshot();
        bool move(std::string gameMove);
        bool move(int x, int y);
        std::string everyLegalMove();
        std::string endState();
        Player checkWinner();

    private:
        TicTacToe(TicTacToe proto, int x, int y);
        std::vector<std::vector<Player>> board;
        bool boardFull();
};

#endif