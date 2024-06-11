#include "Catan.hpp"
#include <iostream>

Catan::Catan(const Player& p1, const Player& p2, const Player& p3)
    : players{p1, p2, p3}, currentPlayerIndex(0) {}

void Catan::ChooseStartingPlayer() {
    // Implement starting player choice logic
    std::cout << players[currentPlayerIndex].getName() << " starts the game." << std::endl;
}

Board& Catan::getBoard() {
    return board;
}

void Catan::printWinner() {
    for (const Player& player : players) {
        if (player.getVictoryPoints() >= 10) {
            std::cout << player.getName() << " wins the game!" << std::endl;
            return;
        }
    }
    std::cout << "None" << std::endl;
}
