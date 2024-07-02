//315144972
//roeyshmil09@gmail.com


#include "Player.hpp"
#include "PlotOfLand.hpp"
#include "DevelopmentCardType.hpp"
#include "VertexPositionType.hpp"
#include "Catan.hpp"
#include "Point2D.hpp"
#include <algorithm>
#include <iostream>



Player::Player(const std::string& name)  : name(name),
    victoryPoints(0),
    knightCards(0),
    monopoly(0),
    buildingRoads(0),
    yearOfAbundance(0),
    isFirstTurn(true),
    hasBiggestArmyCard(false),
    settlementsBuilt(0),
    roadsBuilt(0),
    resources(),
    PromotionCards()
{
// Initialize resources vector for all ResourceType enums
for (int i = 0; i <= static_cast<int>(ResourceType::Iron); ++i) {
    ResourceType type = static_cast<ResourceType>(i);
    if (type != ResourceType::None) {
        resources.push_back(Resource(type));
    }
}

    for (int i = 0; i <= static_cast<int>(PromotionCardType::YearOfAbundance); ++i) {
    PromotionCardType type = static_cast<PromotionCardType>(i);
    if (type != PromotionCardType::None) {
        PromotionCards.push_back(PromotionCard(type));
    }
}


// Seed the random number generator
//srand(static_cast<unsigned int>(time(nullptr)));
srand(40);
}
Player::~Player() {
// Delete dynamically allocated development cards to avoid memory leaks
// for (DevelopmentCard* card : developmentCards) {
//     delete card;
// }
}

std::vector<Resource>& Player::getResources()  
{
return resources;
}

const std::vector<Point2D>& Player::getSettlements() const
{

    return settlements;

}
void Player::placeSettlement(Catan& catan,Board& board, int plotIndex, VertexPositionType position) {
// Check if it's the first turn and the player has built 2 settlements and 2 roads
if (isFirstTurn && settlementsBuilt >= 2 && roadsBuilt >= 2) {
    isFirstTurn = false;  // End the first turn
}

// Check if the player has the required resources (only if it's not the first turn)
if (!isFirstTurn && (!hasResources(ResourceType::Brick, 1) || 
                        !hasResources(ResourceType::Wood, 1) ||
                        !hasResources(ResourceType::Wool, 1) ||
                        !hasResources(ResourceType::Oat, 1))) {
    std::cout<< name <<" doesn't have enough resources to place a settlement." << std::endl;
}

// Get the plot from the board
PlotOfLand plot = board.getPlot(plotIndex);

// Determine the vertex based on the position
Point2D vertex;
switch (position) {
    case VertexPositionType::UpVertex:
        vertex = plot.getUpVertex();
        break;
    case VertexPositionType::UpRightVertex:
        vertex = plot.getUpRightVertex();
        break;
    case VertexPositionType::BottomRightVertex:
        vertex = plot.getBottomRightVertex();
        break;
    case VertexPositionType::BottomVertex:
        vertex = plot.getBottomVertex();
        break;
    case VertexPositionType::BottomLeftVertex:
        vertex = plot.getBottomLeftVertex();
        break;
    case VertexPositionType::UpLeftVertex:
        vertex = plot.getUpLeftVertex();
        break;
    default:
        std::cout<<"Warning to "<<name<<". Invalid vertex position."<<std::endl;
}

// Check if the vertex is already occupied
if (board.isVertexOccupied(vertex)) {
    std::cout<<"Warning to "<<name<<". Vertex is already occupied by a settlement."<<std::endl;
}

// Ensure the new settlement is at least two sections of road away from another settlement
for (const auto& settlement : settlements) {
    if (vertex.distanceTo(settlement) < 2) {
        std::cout<<"Warning to "<<name<<". New settlement must be at least two sections of road away from another settlement."<<std::endl;
    }
}

// Check adjacency rules, but skip this check if it is the first turn
bool isAdjacentToRoad = false;
if (!isFirstTurn) {
    for (const auto& road : roads) {
        if (road.getStart() == vertex || road.getEnd() == vertex) {
            isAdjacentToRoad = true;
            break;
        }
    }
} else {
    isAdjacentToRoad = true;  // Allow placement during the first turn
}

if (!isAdjacentToRoad) {
    std::cout<<"Warning to "<<name<<".Settlement must be adjacent to a road."<<std::endl;
}

// Place the settlement
settlements.push_back(vertex);
board.addSettlement(plotIndex, vertex);

// Deduct the resources (only if it's not the first turn)
if (!isFirstTurn) {
    removeResources(ResourceType::Brick, 1);
    removeResources(ResourceType::Wood, 1);
    removeResources(ResourceType::Wool, 1);
    removeResources(ResourceType::Oat, 1);
}

// Award one victory point
++victoryPoints;

// Increment the count of settlements built during the first turn
if (isFirstTurn) {
    ++settlementsBuilt;

    // Check if the first turn conditions are met after placing the settlement
    if (settlementsBuilt >= 2 && roadsBuilt >= 2) {
        isFirstTurn = false;  // End the first turn
    }
}

std::cout << name <<" has placed a settlement at (" << vertex.getX() << ", " << vertex.getY() << ")" << std::endl;
    if (isFirstTurn)
{
    catan.grantResource(*this,vertex);
}
}



void Player::placeCity(Board& board, Point2D vertex) {
// Check if the player has the required resources
if ((!hasResources(ResourceType::Iron, 3) || !hasResources(ResourceType::Oat, 2)) && !isFirstTurn) {
    std::cout<<"Warning to "<<name<<".You don't have enough resources to place a city."<<std::endl;
    return;
}

// Check if the vertex has an existing settlement
auto it = std::find(settlements.begin(), settlements.end(), vertex);
if (it == settlements.end()) {
        std::cout<<"Warning to "<<name<<". No settlement at the specified vertex to upgrade to a city." <<std::endl;
        return;
}

// Remove the settlement
settlements.erase(it);

// Add the city
cities.push_back(vertex);

// Deduct the resources
removeResources(ResourceType::Iron, 3);
removeResources(ResourceType::Oat, 2);

// Adjust victory points
--victoryPoints; // Lose 1 point from the settlement
victoryPoints += 2; // Gain 2 points for the city

std::cout << "City placed at (" << vertex.getX() << ", " << vertex.getY() << ")" << std::endl;
}


bool Player::placeRoad(Board& board, int plotIndex, VertexPositionType startPos, VertexPositionType endPos) {
// Check if it's the first turn and the player has built 2 settlements and 2 roads
if (isFirstTurn && settlementsBuilt >= 2 && roadsBuilt >= 2) {
    isFirstTurn = false;  // End the first turn
}

// Check if the player has the required resources (only if it's not the first turn)
if (!isFirstTurn && (!hasResources(ResourceType::Brick, 1) || 
                        !hasResources(ResourceType::Wood, 1))) {
    std::cout<<"Warning to "<<name<<". You don't have enough resources to place a road."<< std::endl;
    return false;
}

// Get the plot from the board
PlotOfLand plot = board.getPlot(plotIndex);

// Determine the start and end vertices based on the positions
Point2D start, end;
switch (startPos) {
    case VertexPositionType::UpVertex:
        start = plot.getUpVertex();
        break;
    case VertexPositionType::UpRightVertex:
        start = plot.getUpRightVertex();
        break;
    case VertexPositionType::BottomRightVertex:
        start = plot.getBottomRightVertex();
        break;
    case VertexPositionType::BottomVertex:
        start = plot.getBottomVertex();
        break;
    case VertexPositionType::BottomLeftVertex:
        start = plot.getBottomLeftVertex();
        break;
    case VertexPositionType::UpLeftVertex:
        start = plot.getUpLeftVertex();
        break;
    default:
        std::cout<<"Warning to "<< name <<". Invalid start vertex position."<<std::endl;
        return false;
}

switch (endPos) {
    case VertexPositionType::UpVertex:
        end = plot.getUpVertex();
        break;
    case VertexPositionType::UpRightVertex:
        end = plot.getUpRightVertex();
        break;
    case VertexPositionType::BottomRightVertex:
        end = plot.getBottomRightVertex();
        break;
    case VertexPositionType::BottomVertex:
        end = plot.getBottomVertex();
        break;
    case VertexPositionType::BottomLeftVertex:
        end = plot.getBottomLeftVertex();
        break;
    case VertexPositionType::UpLeftVertex:
        end = plot.getUpLeftVertex();
        break;
    default:
        std::cout<<"Warning to "<< name <<". Invalid end vertex position."<<std::endl;
        return false;
}

// Validate the vertices
std::vector<Point2D> vertices = {
    plot.getUpVertex(),
    plot.getUpRightVertex(),
    plot.getBottomRightVertex(),
    plot.getBottomVertex(),
    plot.getBottomLeftVertex(),
    plot.getUpLeftVertex()
};

bool isValidStart = false;
bool isValidEnd = false;

for (const auto& v : vertices) {
    if (v == start) {
        isValidStart = true;
    }
    if (v == end) {
        isValidEnd = true;
    }
}

if (!isValidStart || !isValidEnd) {
    std::cout<<"Warning to "<< name <<". Please provide valid vertices."<<std::endl;
    return false;
}

// Check adjacency rules
bool isAdjacentToSettlementOrRoad = false;

for (const auto& settlement : settlements) {
    if (start.distanceTo(settlement) <= 1 || end.distanceTo(settlement) <= 1) {
        isAdjacentToSettlementOrRoad = true;
        break;
    }
}

for (const auto& road : roads) {
    if (road.getStart() == start || road.getEnd() == start || road.getStart() == end || road.getEnd() == end) {
        isAdjacentToSettlementOrRoad = true;
        break;
    }
}

if (!isAdjacentToSettlementOrRoad) {
    std::cout <<"Warning to "<< name <<".Road must be adjacent to a settlement or another road."<<std::endl;
    return false;
}

// Place the road
Road newRoad(start, end);
roads.push_back(newRoad);

// Deduct the resources (only if it's not the first turn)
if (!isFirstTurn) {
    removeResources(ResourceType::Brick, 1);
    removeResources(ResourceType::Wood, 1);
}

// Increment the count of roads built during the first turn
if (isFirstTurn) {
    ++roadsBuilt;

    // Check if the first turn conditions are met after placing the road
    if (settlementsBuilt >= 2 && roadsBuilt >= 2) {
        isFirstTurn = false;  // End the first turn
    }
}

std::cout << name <<" has placed a Road between (" << start.getX() << ", " << start.getY() << ") and (" << end.getX() << ", " << end.getY() << ")" << std::endl;
return true;
}



bool Player::hasResources(ResourceType type, int count) {
return std::count_if(resources.begin(), resources.end(), [type](const Resource& resource) {
    return resource.getType() == type;
}) >= count;
}

void Player::removeResources(ResourceType type, int count) {
auto it = resources.begin();
while (count > 0 && it != resources.end()) {
    if (it->getType() == type) {
        it = resources.erase(it);
        --count;
    } else {
        ++it;
    }
}
}

bool Player::findVertexInSettlements(const Point2D& vertex) {
auto it = std::find(settlements.begin(), settlements.end(), vertex);

if (it != settlements.end()) {
    std::cout << "Match found at settlement (" << it->getX() << ", " << it->getY() << ")\n";
    return true;
}


return false;
}



bool Player::hasSettlementAt(const Point2D& vertex)  {
for (int i = 0;i<settlements.size();i++)
{
        std::cout << "Comparing settlement (" << settlements[i].getX() << ", " << settlements[i].getY() << ") with vertex (" << vertex.getX() << ", " << vertex.getY() << ")" << std::endl;
    if (settlements[i] == vertex) {
        return true;
    }
}
return false;
}


void Player::rollDice(Catan& catan,const Board& board) {
// Roll the dice to get a random number between 2 and 12
int diceResult = std::rand() % 11 + 2; // Generate a random number between 2 and 12
std::cout << "Dice result: " << diceResult << std::endl;

// Check which players have settlements or cities neighboring the rolled number
for (int i = 0; i < 19; ++i) {
    PlotOfLand plot = board.getPlot(i);
    if (plot.getNumber() == diceResult) {
        // Check each vertex of the plot
        for (const Point2D& vertex : plot.getVertices()) {
            // for (Player& player : catan.getPlayers()) {
            //     if (player.hasSettlementAt(vertex)) {
            //         catan.grantResource(player, vertex);
            //     }
            // }
            
                
                    
                catan.grantResource(vertex);
                    
                
            
        }
    }
}
}



void Player::trade(Player& otherPlayer, ResourceType offeredResource, ResourceType desiredResource, int offeredAmount, int desiredAmount) {

if ( offeredAmount > resources[static_cast<int>(offeredResource)].getCurrentAmount()) {
    std::cout<<"Invalid trade between "<< name << " and " << otherPlayer.getName() <<"."<<name<<" does not have sufficient offered resource." << std::endl;
    return;
}


if ( desiredAmount > otherPlayer.resources[static_cast<int>(desiredResource)].getCurrentAmount()) {
    std::cout<<"Invalid tradebetween "<< name << " and " << otherPlayer.getName() <<"." << otherPlayer.getName() << " does not have sufficient desired resource." << std::endl;
    return;
}

// Perform the trade

//reduce
resources[static_cast<int>(offeredResource)].changeAmount(-offeredAmount);
otherPlayer.resources[static_cast<int>(desiredResource)].changeAmount(-desiredAmount);

//add
resources[static_cast<int>(desiredResource)].changeAmount(desiredAmount);
otherPlayer.resources[static_cast<int>(offeredResource)].changeAmount(offeredAmount);

std::cout << "trade between " <<name<<" and " << otherPlayer.getName() <<" was done successfully !" <<" "<<
offeredAmount <<" "<< offeredResource <<" <-->"  <<" "<< desiredAmount<<" "<< desiredResource <<std::endl;

}

void Player::buyDevelopmentCard() {

if (resources[static_cast<int>(ResourceType::Iron)].getCurrentAmount() < 1 || resources[static_cast<int>(ResourceType::Wool)].getCurrentAmount() < 1 || resources[static_cast<int>(ResourceType::Oat)].getCurrentAmount() < 1) {
    std::cout<< name <<" has insufficient resources to buy a development card."<< std::endl;
    return;
}

resources[static_cast<int>(ResourceType::Iron)].changeAmount(-1);
resources[static_cast<int>(ResourceType::Wool)].changeAmount(-1);
resources[static_cast<int>(ResourceType::Oat)].changeAmount(-1);



// Generate a random number between 0 and 2
int randomNum = rand() % 3;
size_t random;
DevelopmentCardType cardType; 

switch (randomNum) {
    case 0:
        random = std::rand()%3;
        PromotionCardType pc_type;
        switch(random)
        {
            case 0:
                pc_type = PromotionCardType::Monopoly;
                monopoly++;
                break;
            case 1:
                pc_type = PromotionCardType::BuildingRoads;
                buildingRoads++;
                break;
            case 2:
                pc_type = PromotionCardType::YearOfAbundance;
                yearOfAbundance++;
                break;


        }
        PromotionCards.push_back(PromotionCard(pc_type));
        cardType = DevelopmentCardType::Promotion;
        break;
    case 1:
        VictoryPointCards.push_back(VictoryPointCard());
        cardType = DevelopmentCardType::VictoryPoint;
        
        break;
    case 2:
        KnightCards.push_back(KnightCard());
        cardType = DevelopmentCardType::Knight;
        if(KnightCards.size() >= 3)
            hasBiggestArmyCard = true;
        break;
    default:
        break;
}

std::cout << name << " bought a " << "'"<< cardType << "'" << " card succesfully !" << "\n";

}


void Player::useDevelopmentCard(Catan& catan,DevelopmentCardType type)
{
    switch(type) {
    case DevelopmentCardType::Promotion: 
    {
        int index;
        std::cout << "Choose promotion card type: " << "\n";
        std::cout << "1. Monopoly" << "\n";
        std::cout << "2. Building Roads" << "\n";
        std::cout << "3. Year of Abundance" << "\n";
        std::cin >> index;
        switch(index) {
            case 1: {
                
                // Monopoly: Take all resources of one type from all other players
                std::cout << "You chose the Monopoly card. Choose resource type: " << "\n";
                std::cout << "1. Wood" << "\n";
                std::cout << "2. Brick" << "\n";
                std::cout << "3. Wool" << "\n";
                std::cout << "4. Oat" << "\n";
                std::cout << "5. Iron" << "\n";
                int resourceIndex;
                std::cin >> resourceIndex;
                ResourceType chosenResource = static_cast<ResourceType>(resourceIndex - 1);
                

                for (Player& player : catan.getPlayers()) {
                    if (&player != this) {  // Skip the current player
                        int amount = 0;

                        //take specific chosen resource from other players
                        for (Resource& resource : player.resources) {
                            if (resource.getType() == chosenResource) {
                                amount += resource.getCurrentAmount();
                                resource.resetAmount();
                            }
                        }
                        //add my resource 
                        for (Resource& resource : resources) {
                            if (resource.getType() == chosenResource) {
                                resource.changeAmount(amount);
                            }
                        }
                    }
                }

                std::cout<< name<< " has got "<< chosenResource << " from all other players!" <<std::endl;
                break;
            }
            case 2:
            {
                // Building Roads: Build two free roads
                std::cout << "You chose the Building Roads card." << std::endl;
                buildingRoads += 2;
                std::cout<<"Enter plotIndex,and 2 numbers represents the position of the vertex relative to plot(1-6 where 1 is the upVertex clockwise) sepereated by a space: (For example: 4 1 2 )";
                int plotIndex1,n1,n2;
                int plotIndex2,n3,n4;
                std::cin >> plotIndex1 >> n1 >> n2;
                VertexPositionType type1 =VertexPosition::convertToVertexPositionType(n1);
                VertexPositionType type2 =VertexPosition::convertToVertexPositionType(n2);
                Catan c;
                if(placeRoad(c.getBoard(),plotIndex1,type1,type2))
                    buildingRoads++;
                std::cout<<"Enter another plotIndex,and 2 numbers represents the position of the vertex relative to plot(1-6 where 1 is the upVertex clockwise) sepereated by a space: (For example: 4 1 2 )";    
                std::cin >> plotIndex2 >> n3 >> n4;
                VertexPositionType type3 =VertexPosition::convertToVertexPositionType(n3);
                VertexPositionType type4 =VertexPosition::convertToVertexPositionType(n4);
                if(placeRoad(c.getBoard(),plotIndex2,type3,type4))
                    buildingRoads++;
                break;
            }
            case 3:
            {
                // Year of Abundance: Take any two resources from the bank
                std::cout << "You used the Year of Abundance card. Choose two resources: " << "\n";
                std::cout << "1. Wood" << "\n";
                std::cout << "2. Brick" << "\n";
                std::cout << "3. Wool" << "\n";
                std::cout << "4. Oat" << "\n";
                std::cout << "5. Iron" << "\n";
                int resourceIndex1, resourceIndex2;
                std::cin >> resourceIndex1 >> resourceIndex2;
                resources[resourceIndex1 - 1].changeAmount(1);
                resources[resourceIndex2 - 1].changeAmount(1);
                std::cout << name<< " has got 1 "<< resources[resourceIndex1 - 1].getType() <<" and 1 " <<resources[resourceIndex2 - 1].getType()<<" from the bank of Catan" <<std::endl;
                break;


            
            }
        
    }
    case DevelopmentCardType::VictoryPoint:
    {
        
        std::cout << "Victory Point already added to total points." << std::endl;
        
        break;
    }
    case DevelopmentCardType::Knight:
    {
        if(!KnightCards.empty()) {
            // Assume we remove the card after use
            knightCards++;
            KnightCards.pop_back();
            std::cout << "You chose a Knight card. Current knight count: " << knightCards << std::endl;
            // Check for Largest Army bonus if applicable
            // Placeholder logic to check for Largest Army
            break;
        } else {
            std::cout << "No Knight cards to use." << std::endl;
        }
        break;
    }
    default:
        std::cout << "Invalid development card type." << std::endl;
        break;
}

}
}


void Player::showAllResources()
{
std::cout<< "||||||||||  Resources |||||||||| "<< std::endl;

std::cout<< "Current resources of "<<name << ":" <<std::endl;
std::cout << ResourceType::Wood <<": " << resources[static_cast<int>(ResourceType::Wood)].getCurrentAmount() << std::endl;
std::cout << ResourceType::Brick <<": " << resources[static_cast<int>(ResourceType::Brick)].getCurrentAmount() << std::endl;
std::cout << ResourceType::Wool <<": " << resources[static_cast<int>(ResourceType::Wool)].getCurrentAmount() << std::endl;
std::cout << ResourceType::Oat <<": " << resources[static_cast<int>(ResourceType::Oat)].getCurrentAmount() << std::endl;
std::cout << ResourceType::Iron <<": " << resources[static_cast<int>(ResourceType::Iron)].getCurrentAmount() << std::endl;
std::cout<<std::endl;
std::cout<< "||||||||||||||||||||||||||||||||| "<< std::endl;
}


void Player::endTurn() {

// Check if the player has more than 10 victory points
if (victoryPoints >= 10) {
    std::cout << getName() << " has won the game with " << victoryPoints << " victory points!" << std::endl;
} else {
    std::cout << getName() << " ends the turn with " << victoryPoints << " victory points." << std::endl;
}
}

void Player::printPoints() const {

std::cout << name << " has " << victoryPoints << " points." << std::endl;
}

const std::string& Player::getName() const {
return name;
}

int Player::getVictoryPoints() const {
return victoryPoints;
}


