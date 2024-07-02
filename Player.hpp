#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Resource.hpp"
#include "DevelopmentCard.hpp"
#include "Board.hpp"
#include "PromotionCard.hpp"
#include "VictoryPointCard.hpp"
#include "KnightCard.hpp"
#include "DevelopmentCardType.hpp"
#include "Road.hpp"
#include "VertexPositionType.hpp"
#include <string>
#include <vector>
#include <map>
//#include "Catan.hpp" 
class Catan;


class Player 
{
private:
    std::string name;
    std::vector<Resource> resources;
    int currentPoints;
    int knightCards;
    int victoryPoints;
    int knightPoints;
    int monopoly;
    int buildingRoads;
    int yearOfAbundance;
    bool isFirstTurn;
    bool hasBiggestArmyCard;
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
    std::vector<Resource>& getResources();
    const std::vector<Point2D>& getSettlements() const ;
    bool placeRoad(Board& board, int plotIndex, VertexPositionType start, VertexPositionType end);
    void placeSettlement(Catan& catan,Board& board, int plotIndex,VertexPositionType position);
    void placeCity(Board& board, Point2D vertex);
    bool hasResources(ResourceType type, int count);
    void removeResources(ResourceType type, int count);
    void rollDice(Catan& catan,const Board& board);
    void showAllResources();
    void trade(Player& otherPlayer, ResourceType offeredResource, ResourceType desiredResource, int offeredAmount, int desiredAmount);
    void buyDevelopmentCard();
    void useDevelopmentCard(Catan& catan,DevelopmentCardType type);
    void endTurn();
    bool findVertexInSettlements(const Point2D& vertex);
    bool hasSettlementAt(const Point2D& vertex);
    void printPoints() const;
    const std::string& getName() const;
    int getVictoryPoints() const;
};

#endif 
