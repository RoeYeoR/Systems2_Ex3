#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Resource.hpp"
#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include "PromotionCard.hpp"
#include "VictoryPointCard.hpp"
#include "KnightCard.hpp"

class Player {
private:
    std::string name;
    int victoryPoints;
    int knightCards; 
    int PromotionCards;
    std::vector<Resource> resources;
    std::vector<DevelopmentCard*> developmentCards;
    std::vector<std::string> settlements; 
    std::vector<std::string> cities;      


public:
    Player(const std::string& name);
    ~Player();
   
    void placeSettlement(const std::vector<std::string>& pieceNames, const std::vector<int>& numbers, const Board& board);
    void placeRoad(const std::vector<std::string>& pieceNames, const std::vector<int>& numbers, const Board& board);
    void rollDice(const Board& board);
    void buildRoad();
    void buildSettlement();
    void buildCity();
    void trade(Player& otherPlayer, ResourceType offeredResource, ResourceType desiredResource, int offeredAmount, int desiredAmount);
    void buyDevelopmentCard();
    void endTurn();
    void printPoints() const;

    const std::string& getName() const;
    int getVictoryPoints() const;
};

#endif // PLAYER_HPP
