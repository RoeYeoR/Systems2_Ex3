#include "Player.hpp"
#include "PlotOfLand.hpp"
#include <iostream>


Player::Player(const std::string& name) : name(name), victoryPoints(2) 
   { 
      // Seed the random number generator
      srand(time(nullptr));
   }

   Player::~Player() {
    // Delete dynamically allocated development cards to avoid memory leaks
    for (DevelopmentCard* card : developmentCards) {
        delete card;
    }
   }

void Player::placeSettlement(const std::vector<std::string>& pieceNames, const std::vector<int>& numbers, const Board& board) {
    // Check if the vectors are of the same size
    if (pieceNames.size() != numbers.size()) {
        throw std::invalid_argument("Invalid input: pieceNames and numbers vectors must have the same size.");
    }

    // Iterate through each piece and number
    for (size_t i = 0; i < pieceNames.size(); ++i) {
        // Get the plot at the specified index
        PlotOfLand plot = board.getPlot(numbers[i]);

        // Check if the piece name matches the one specified and if it's a valid place for a settlement
        if (plot.getLandType() == pieceNames[i]){ //&& /* Add condition to check validity */) {
            // Place the settlement
            // Update player's resources, victory points, etc.
            // Example: playerResources[plot.resource]--; // Decrement resource count for the player
            // Example: victoryPoints++; // Increment victory points for the player
        } else {
            // Handle invalid placement
            throw std::invalid_argument("Invalid placement: Cannot place settlement at the specified location.");
        }
    }
}


void Player::placeRoad(const std::vector<std::string>& pieceNames, const std::vector<int>& numbers, const Board& board) {
    // Check if the vectors are of the same size
    if (pieceNames.size() != numbers.size()) {
        throw std::invalid_argument("Invalid input: pieceNames and numbers vectors must have the same size.");
    }

    // Iterate through each piece and number
    for (size_t i = 0; i < pieceNames.size(); ++i) {
        // Get the plot at the specified index
        PlotOfLand plot = board.getPlot(numbers[i]);

        // Check if the piece name matches the one specified and if it's a valid place for a road
        if (plot.getLandType() == pieceNames[i]){ //&& /* Add condition to check validity */) {
            // Place the road
            // Update player's resources, victory points, etc.
            // Example: playerResources[plot.resource]--; // Decrement resource count for the player
            // Example: victoryPoints++; // Increment victory points for the player
        } else {
            // Handle invalid placement
            throw std::invalid_argument("Invalid placement: Cannot place road at the specified location.");
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

void Player::buildRoad() {
    // Check if player has sufficient resources to build a road
    // Assuming the resources required for a road are 1 brick and 1 wood
    bool hasBrick = false;
    bool hasWood = false;
    for (auto& resource : resources) {
        if (resource.getType() == ResourceType::Brick) {
            hasBrick = true;
        } else if (resource.getType() == ResourceType::Wood) {
            hasWood = true;
        }
    }

    // If player has sufficient resources, deduct the resources and build the road
    if (hasBrick && hasWood) {
        // Deduct resources
        int brickToRemove = 1;
        int woodToRemove = 1;
        for (auto it = resources.begin(); it != resources.end();) {
            if (it->getType() == ResourceType::Brick && brickToRemove > 0) {
                it = resources.erase(it);
                brickToRemove--;
            } else if (it->getType() == ResourceType::Wood && woodToRemove > 0) {
                it = resources.erase(it);
                woodToRemove--;
            } else {
                ++it;
            }
    } 
    }
    else {
        std::cout << "Insufficient resources to build a road." << std::endl;
    }
}

void Player::buildSettlement() {
    // Check if player has sufficient resources to build a settlement
    // Assuming the resources required for a settlement are 1 brick, 1 wood, 1 wool, and 1 oat
    bool hasBrick = false;
    bool hasWood = false;
    bool hasWool = false;
    bool hasOat = false;
    for (auto& resource : resources) {
        if (resource.getType() == ResourceType::Brick) {
            hasBrick = true;
        } else if (resource.getType() == ResourceType::Wood) {
            hasWood = true;
        } else if (resource.getType() == ResourceType::Wool) {
            hasWool = true;
        } else if (resource.getType() == ResourceType::Oat) {
            hasOat = true;
        }
    }

    // If player has sufficient resources, deduct the resources and build the settlement
    if (hasBrick && hasWood && hasWool && hasOat) {
        // Deduct resources
        int brickToRemove = 1;
        int woodToRemove = 1;
        int woolToRemove = 1;
        int oatToRemove = 1;
        for (auto it = resources.begin(); it != resources.end();) {
            if (it->getType() == ResourceType::Brick && brickToRemove > 0) {
                it = resources.erase(it);
                brickToRemove--;
            } else if (it->getType() == ResourceType::Wood && woodToRemove > 0) {
                it = resources.erase(it);
                woodToRemove--;
            } else if (it->getType() == ResourceType::Wool && woolToRemove > 0) {
                it = resources.erase(it);
                woolToRemove--;
            } else if (it->getType() == ResourceType::Oat && oatToRemove > 0) {
                it = resources.erase(it);
                oatToRemove--;
            } else {
                ++it;
            }
        }

        // Build the settlement
        // Implementation logic for building settlement goes here
        // For example, you might add the settlement to the player's list of settlements
        settlements.push_back("Settlement"); // Example: Add a settlement to the player's
    } else {
        std::cout << "Insufficient resources to build a settlement." << std::endl;
    }

}
void Player::buildCity() {
     // Check if player has sufficient resources to build a city
    // Assuming the resources required for a city are 3 iron and 2 oats
    bool hasIron = false;
    bool hasOats = false;
    int ironCount = 0;
    int oatCount = 0;
    for ( auto& resource : resources) {
        if (resource.getType() == ResourceType::Iron) {
            ironCount++;
        } else if (resource.getType() == ResourceType::Oat) {
            oatCount++;
        }
    }
    if (ironCount >= 3 && oatCount >= 2) {
        hasIron = true;
        hasOats = true;
    }

    // If player has sufficient resources, deduct the resources and build the city
    if (hasIron && hasOats) {
        // Deduct resources
        int ironToRemove = 3;
        int oatsToRemove = 2;
        for (auto it = resources.begin(); it != resources.end();) {
            if (it->getType() == ResourceType::Iron && ironToRemove > 0) {
                it = resources.erase(it);
                ironToRemove--;
            } else if (it->getType() == ResourceType::Oat && oatsToRemove > 0) {
                it = resources.erase(it);
                oatsToRemove--;
            } else {
                ++it;
            }
        }

        // Build the city
        // Implementation logic for building city goes here
        // For example, you might add the city to the player's list of cities
        cities.push_back("City"); // Example: Add a city to the player's list of cities
    } else {
        std::cout << "Insufficient resources to build a city." << std::endl;
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
    resources[offeredIndex].changeAmount(-offeredAmount);
    otherPlayer.resources[desiredIndex].changeAmount(-desiredAmount);

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

    // Create an instance of a concrete subclass of DevelopmentCard based on the random number
    switch (randomNum) {
        case 0:
            developmentCards.push_back(new PromotionCard());
            break;
        case 1:
            developmentCards.push_back(new VictoryPointCard());
            break;
        case 2:
            developmentCards.push_back(new KnightCard());
            break;
        default:
            break;
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

