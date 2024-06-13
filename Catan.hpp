#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "Player.hpp"
#include "Board.hpp"

class Catan {
private:
    std::vector<Player> players;
    Board board;
    int currentPlayerIndex;

public:
    Catan(const Player& p1, const Player& p2, const Player& p3);

    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner();
    void transferResource(Player& from, Player& to, const ResourceType& resource, int amount);
};

#endif // CATAN_HPP
