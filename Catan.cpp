#include "Catan.hpp"
#include <iostream>
#include <sstream>
#include "Resource.hpp"

Catan::Catan(const Player& p1, const Player& p2, const Player& p3)
    : players{p1, p2, p3}, currentPlayerIndex(0) {}

void Catan::ChooseStartingPlayer() {
    // Implement starting player choice logic
    std::cout << players[currentPlayerIndex].getName() << " starts the game." << "\n" << "\n";
}

Board& Catan::getBoard() {
    return board;
}


void transferResource(Player& from, Player& to, const ResourceType& resource, int amount)
{
    int desiredIndex = -1;
    for (size_t i = 0; i < from.getResources().size(); ++i) {
        if (from.getResources()[i].getType() == resource) {
            desiredIndex = i;
            break;
        }
    }
    if (desiredIndex == -1 || from.getResources()[desiredIndex].getCurrentAmount() ==0 ) {
        std::stringstream ss;
        ss << "Invalid trade: " << from.getName() << " does not have  " << resource << "\n" ;
        throw std::invalid_argument(ss.str());
        
    }

    to.getResources()[desiredIndex].changeAmount(from.getResources()[desiredIndex].getCurrentAmount());
    from.getResources()[desiredIndex].resetAmount();


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
