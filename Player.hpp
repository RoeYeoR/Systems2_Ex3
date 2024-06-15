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
#include "Road.hpp"
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
    bool isFirstTurn;
    int settlementsBuilt; 
    int roadsBuilt;  

    std::vector<PromotionCard> PromotionCards;
    std::vector<VictoryPointCard> VictoryPointCards;
    std::vector<KnightCard> KnightCards;


   
    std::vector<Road>roads;
    std::vector<Point2D> settlements; 
    std::vector<Point2D> cities;      


public:
     Player(const std::string& name);
    ~Player();
   
    std::vector<Resource> getResources();
    void placeRoad(Board& board, int plotIndex, Point2D start, Point2D end);
    void placeSettlement(Board& board, int plotIndex, Point2D vertex);
    void placeCity(Board& board, Point2D vertex);
    bool hasResources(ResourceType type, int count);
    void removeResources(ResourceType type, int count);
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
