#include "Player.hpp"
#include "PlotOfLand.hpp"
#include "DevelopmentCardType.hpp"
#include <algorithm>
#include <iostream>



Player::Player(const std::string& name) : name(name), victoryPoints(2), knightCards(0),monopoly(0), buildingRoads(0),yearOfAbundance(0) ,isFirstTurn(true)
   { 
      // Seed the random number generator
      srand(time(nullptr));

   }

   Player::~Player() {
    // Delete dynamically allocated development cards to avoid memory leaks
    // for (DevelopmentCard* card : developmentCards) {
    //     delete card;
    // }
   }

   std::vector<Resource> Player::getResources()
   {
    return this->resources;
   }
 void Player::placeSettlement(Board& board, int plotIndex, Point2D vertex) {
        // Check if it's the first turn and the player has built 2 settlements and 2 roads
        if (isFirstTurn && settlementsBuilt >= 2 && roadsBuilt >= 2) {
            isFirstTurn = false;  // End the first turn
        }

        // Check if the player has the required resources (only if it's not the first turn)
        if (!isFirstTurn && (!hasResources(ResourceType::Brick, 1) || 
                             !hasResources(ResourceType::Wood, 1) ||
                             !hasResources(ResourceType::Wool, 1) ||
                             !hasResources(ResourceType::Oat, 1))) {
            throw std::invalid_argument("Not enough resources to place a settlement.");
        }

        // Get the plot from the board
        PlotOfLand plot = board.getPlot(plotIndex);

        // Validate the vertex
        std::vector<Point2D> vertices = {
            plot.getUpVertex(),
            plot.getUpRightVertex(),
            plot.getBottomRightVertex(),
            plot.getBottomVertex(),
            plot.getBottomLeftVertex(),
            plot.getUpLeftVertex()
        };

        bool isValidVertex = false;
        for (const auto& v : vertices) {
            if (v == vertex) {
                isValidVertex = true;
                break;
            }
        }

        if (!isValidVertex) {
            throw std::invalid_argument("Invalid vertex specified.");
        }

        // Check if the vertex is already occupied
        if (board.isVertexOccupied(vertex)) {
            throw std::invalid_argument("Vertex is already occupied by a settlement.");
        }

        // Ensure the new settlement is at least two sections of road away from another settlement
        for (const auto& settlement : settlements) {
            if (vertex.distanceTo(settlement) < 2) {
                throw std::invalid_argument("New settlement must be at least two sections of road away from another settlement.");
            }
        }

        // Check adjacency rules
        bool isAdjacentToRoad = false;
        for (const auto& road : roads) {
            if (road.getStart() == vertex || road.getEnd() == vertex) {
                isAdjacentToRoad = true;
                break;
            }
        }

        if (!isAdjacentToRoad) {
            throw std::invalid_argument("Settlement must be adjacent to a road.");
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

        std::cout << "Settlement placed at (" << vertex.getX() << ", " << vertex.getY() << ")" << std::endl;
    }


void Player::placeCity(Board& board, Point2D vertex) {
    // Check if the player has the required resources
    if ((!hasResources(ResourceType::Iron, 3) || !hasResources(ResourceType::Oat, 2)) && !isFirstTurn) {
        throw std::invalid_argument("Not enough resources to place a city.");
    }

    // Check if the vertex has an existing settlement
    auto it = std::find(settlements.begin(), settlements.end(), vertex);
    if (it == settlements.end()) {
        throw std::invalid_argument("No settlement at the specified vertex to upgrade to a city.");
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


void Player::placeRoad(Board& board, int plotIndex, Point2D start, Point2D end) {
    // Check if it's the first turn and the player has built 2 settlements and 2 roads
    if (isFirstTurn && settlementsBuilt >= 2 && roadsBuilt >= 2) {
        isFirstTurn = false;  // End the first turn
    }

    // Check if the player has the required resources (only if it's not the first turn)
    if (!isFirstTurn && (!hasResources(ResourceType::Brick, 1) || 
                         !hasResources(ResourceType::Wood, 1))) {
        throw std::invalid_argument("Not enough resources to place a road.");
    }

    // Get the plot from the board
    PlotOfLand plot = board.getPlot(plotIndex);

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
        throw std::invalid_argument("Invalid vertices specified.");
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
        throw std::invalid_argument("Road must be adjacent to a settlement or another road.");
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

    std::cout << "Road placed between (" << start.getX() << ", " << start.getY() << ") and (" << end.getX() << ", " << end.getY() << ")" << std::endl;
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


void Player::rollDice(const Board& board) {
    // Roll the dice to get a random number between 2 and 12
   
    int diceResult = std::rand() % 11 + 2; // Generate a random number between 2 and 12
    std::cout << "Dice result: " << diceResult << std::endl;

    // Check which players have settlements or cities neighboring the rolled number
    for (int i = 0; i < 19; ++i) {
        PlotOfLand plot = board.getPlot(i);
        if (plot.getNumber() == diceResult) {
            // Grant resources to players with settlements or cities neighboring this plot
            // Example: playerResources[plot.resource]++; // Increment resource count for the player
        }
    }
}



void Player::trade(Player& otherPlayer, ResourceType offeredResource, ResourceType desiredResource, int offeredAmount, int desiredAmount) {
    // Check if the player has the offered resource in sufficient quantity
    int offeredIndex = -1;
    for (size_t i = 0; i < resources.size(); ++i) {
        if (resources[i].getType() == offeredResource) {
            offeredIndex = i;
            break;
        }
    }
    if (offeredIndex == -1 || offeredAmount > resources[offeredIndex].getCurrentAmount()) {
        throw std::invalid_argument("Invalid trade: Player does not have sufficient offered resource.");
    }

    // Check if the other player has the desired resource in sufficient quantity
    int desiredIndex = -1;
    for (size_t i = 0; i < otherPlayer.resources.size(); ++i) {
        if (otherPlayer.resources[i].getType() == desiredResource) {
            desiredIndex = i;
            break;
        }
    }
    if (desiredIndex == -1 || desiredAmount > otherPlayer.resources[desiredIndex].getCurrentAmount()) {
        throw std::invalid_argument("Invalid trade: Other player does not have sufficient desired resource.");
    }

    // Perform the trade

    //reduce
    resources[offeredIndex].changeAmount(-offeredAmount);
    otherPlayer.resources[desiredIndex].changeAmount(-desiredAmount);

    //add
    resources[desiredIndex].changeAmount(desiredAmount);
    otherPlayer.resources[offeredIndex].changeAmount(offeredAmount);

}

void Player::buyDevelopmentCard() {
    // Define the cost of a development card
    const int IRON_COST = 1;
    const int WOOL_COST = 1;
    const int OATS_COST = 1;

    // Check if the player has sufficient resources to buy a development card
    int ironCount = 0;
    int woolCount = 0;
    int oatsCount = 0;
    for (Resource& res : resources) {
        switch (res.getType()) {
            case ResourceType::Iron:
                ironCount++;
                break;
            case ResourceType::Wool:
                woolCount++;
                break;
            case ResourceType::Oat:
                oatsCount++;
                break;
            default:
                break;
        }
    }

    if (ironCount < IRON_COST || woolCount < WOOL_COST || oatsCount < OATS_COST) {
        throw std::invalid_argument("Insufficient resources to buy a development card.");
    }

    // Deduct the cost of a development card from the player's resources
    for (int i = 0; i < IRON_COST; ++i) {
        for (size_t j = 0; j < resources.size(); ++j) {
            if (resources[j].getType() == ResourceType::Iron) {
                resources.erase(resources.begin() + j);
                break;
            }
        }
    }
    for (int i = 0; i < WOOL_COST; ++i) {
        for (size_t j = 0; j < resources.size(); ++j) {
            if (resources[j].getType() == ResourceType::Wool) {
                resources.erase(resources.begin() + j);
                break;
            }
        }
    }
    for (int i = 0; i < OATS_COST; ++i) {
        for (size_t j = 0; j < resources.size(); ++j) {
            if (resources[j].getType() == ResourceType::Oat) {
                resources.erase(resources.begin() + j);
                break;
            }
        }
    }

    // Generate a random number between 0 and 2
    int randomNum = rand() % 3;
    size_t random;
    DevelopmentCardType cardType; 
    // Create an instance of a concrete subclass of DevelopmentCard based on the random number
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
            victoryPoints++;
            break;
        case 2:
            KnightCards.push_back(KnightCard());
            cardType = DevelopmentCardType::Knight;
            knightCards++;
            break;
        default:
            break;
    }
    
    std::cout << name << "got a " << cardType << " card !" << "\n";

}


 void Player::useDevelopmentCard(DevelopmentCardType type)
 {
    switch(type)
    {
        case DevelopmentCardType::Promotion:
            int index;
            std::cout << "Choose promotion card type: " << "\n";
            std::cout << "1.monopoly"<<"\n";
            std::cout << "2.buildingRoads"<<"\n";
            std::cout << "3.yearOfAbundance" << "\n";
            std::cin >> index;
            switch(index)
            {
                case 1:
                
                   break;

                case 2:
                    break;

                case 3:
                    break;
            }



        case DevelopmentCardType::VictoryPoint:
            if(victoryPoints>0)
            {
                //VictoryPointCard::use();
            }



    }



 }

void Player::endTurn() {
    // Implement end turn logic
    std::cout << name << " ended their turn." << std::endl;
}

void Player::printPoints() const {
    // Calculate the total number of points based on settlements, cities, knight cards, and victory point cards
    int totalPoints = settlements.size() + (cities.size() * 2) + (knightCards == 3 ? 2 : 0);

    // Add points for victory point cards (assuming they are already tracked)
    totalPoints += victoryPoints;

    // Print the player's name and total points
    std::cout << name << " has " << totalPoints << " points." << std::endl;
}

const std::string& Player::getName() const {
    return name;
}

int Player::getVictoryPoints() const {
    return victoryPoints;
}


