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
#include "DevelopmentCardType.hpp"
#include <map>

class Player {
private:
    std::string name;
    std::vector<Resource> resources;
    int knightCards;
    int victoryPoints;
    int monopoly;
    int buildingRoads;
    int yearOfAbundance;
    //std::map<DevelopmentCardType,int> cardsDictionary;
    
    std::vector<PromotionCard> PromotionCards;
    std::vector<VictoryPointCard> VictoryPointCards;
    std::vector<KnightCard> KnightCards;

    std::vector<std::string> settlements; 
    std::vector<std::string> cities;      


public:
     Player(const std::string& name);
    ~Player();
   
    std::vector<Resource> getResources();
    void placeSettlement(const std::vector<std::string>& pieceNames, const std::vector<int>& numbers, const Board& board);
    void placeRoad(const std::vector<LandType>& pieceNames, const std::vector<int>& numbers, const Board& board);
    void rollDice(const Board& board);
    void buildRoad();
    void buildSettlement();
    void buildCity();
    void trade(Player& otherPlayer, ResourceType offeredResource, ResourceType desiredResource, int offeredAmount, int desiredAmount);
    void buyDevelopmentCard();
    void useDevelopmentCard(DevelopmentCardType type);
    void endTurn();
    void printPoints() const;

    const std::string& getName() const;
    int getVictoryPoints() const;
};

#endif // PLAYER_HPP
