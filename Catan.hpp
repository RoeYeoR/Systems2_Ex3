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
    Catan();
    Catan(Player& p1, Player& p2, Player& p3);
    std::vector<Player>& getPlayers();
    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner();
    void transferResource(Player& from, Player& to, const ResourceType& resource, int amount);
    void grantResource(Player& p,Point2D position);
    void grantResource(Point2D position);
};

#endif // CATAN_HPP
