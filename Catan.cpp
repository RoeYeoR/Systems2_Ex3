//315144972
//roeyshmil09@gmail.com

#include "Catan.hpp"
#include <iostream>
#include <sstream>
#include <functional>
#include "Resource.hpp"
#include "Player.hpp"


Catan::Catan()
{
}
Catan::Catan(Player &p1, Player &p2, Player &p3)
    : players{(p1), (p2), (p3)}, currentPlayerIndex(0) {}

void Catan::ChooseStartingPlayer()
{
    // Implement starting player choice logic
    std::cout << players[currentPlayerIndex].getName() << " starts the game." << "\n"
            << "\n";
}

Board& Catan::getBoard() {
return board;
}

std::vector<Player>& Catan::getPlayers() {
    return players;
}

void Catan::transferResource(Player& from, Player& to, const ResourceType& resource, int amount)
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

void Catan::grantResource(Player& p,Point2D position)
{
std::vector<PlotOfLand> plots = board.getPlots();
for(int i=0;i<plots.size();i++)
{
    for(int j = 0; j<6 ;j++)
    {
        if(plots[i].getVertices()[j] == position )
        {
            ResourceType plotRt = plots[i].getResource().getType();
            p.getResources()[static_cast<int>(plotRt)].changeAmount(1);
            std::cout << p.getName() << " has got "<< plotRt << ".\n";
        }

    }

}


}

void Catan::grantResource(Point2D position)
{
for(Player& p : players)
{
    if(p.findVertexInSettlements(position))
    {
        grantResource(p,position);
    }
}


}

void Catan::printWinner() {
for (const Player& player : players) {
    if (player.getVictoryPoints() >= 10) {
        std::cout << player.getName() << " has wom the game!" << std::endl;
        return;
    }
}
std::cout << "No one is winning this Game..." << std::endl;
}
