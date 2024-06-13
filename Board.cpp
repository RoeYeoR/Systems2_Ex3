#include "Board.hpp"
#include "Resource.hpp"
#include "PlotOfLand.hpp"
#include <random>
#include "../../../../../../usr/include/c++/11/bits/algorithmfwd.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
      // Define resources and piece names for each plot of land
    std::vector<Resource> resources = {
        Resource(ResourceType::Iron),
        Resource(ResourceType::Wool),
        Resource(ResourceType::Oat),
        Resource(ResourceType::Wood),
        Resource(ResourceType::Brick),
        Resource(ResourceType::None), // Desert
        Resource(ResourceType::Oat),
        Resource(ResourceType::Wood),
        Resource(ResourceType::Brick),
        Resource(ResourceType::Iron),
        Resource(ResourceType::Wood),
        Resource(ResourceType::Wool),
        Resource(ResourceType::Wool),
        Resource(ResourceType::Oat),
        Resource(ResourceType::Wood),
        Resource(ResourceType::Oat),
        Resource(ResourceType::Brick),
        Resource(ResourceType::Iron),
        Resource(ResourceType::Wool)
    };

    std::vector<LandType> land_Types = {
        LandType::Mountains,
        LandType::PastureLand,
        LandType::AgriculturalLand,
        LandType::Forest,
        LandType::Hills,
        LandType::Desert, // Desert
        LandType::Forest,
        LandType::Hills,
        LandType::AgriculturalLand,
        LandType::Mountains,
        LandType::Forest,
        LandType::PastureLand,
        LandType::PastureLand,
        LandType::AgriculturalLand,
        LandType::Forest,
        LandType::AgriculturalLand,
        LandType::Hills,
        LandType::Mountains,
        LandType::PastureLand
    };

    // Define the numbers according to the instructions
    std::vector<int> numbers = {
        2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
    };

    // Initialize random seed
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the resources and land types
    std::shuffle(resources.begin(), resources.end(), g);
    std::shuffle(land_Types.begin(), land_Types.end(), g);

    int plotCount = 19;

    // Assign resources, land types, and numbers to plots
    for (int i = 0; i < plotCount; ++i) {
        PlotOfLand plot;
        plot.setlandType(land_Types[i]);
        plot.setResource(resources[i].getType());

        if (land_Types[i] == LandType::Desert) {
            plot.setNumber(0);
        } else {
            plot.setNumber(numbers.back());
            numbers.pop_back();
        }

        plots.push_back(plot);
    }
}

void Board::printBoard()
{
     // Define the layout of the board
    std::vector<std::vector<int>> layout = {
        {0, 1, 2},
        {3, 4, 5, 6},
        {7, 8, 9, 10, 11},
        {12, 13, 14, 15},
        {16, 17, 18}
    };

    // Print the board
    for (const auto& row : layout) {
        std::cout << std::setw(6 * (5 - row.size())) << ""; // Adjust spacing for center alignment
        for (const auto& plotIndex : row) {
            const auto& plot = plots[plotIndex];
            std::cout << plot.getLandType() << "(" << plot.getNumber() << ")    ";
        }
        std::cout << "(" << row.size() << ")" << std::endl; // Print the number of plots in the row
    }
    


}


PlotOfLand Board::getPlot(int index) const {
    if (index >= 0 && index < plots.size()) {
        return plots[index];
    }
    else{
        std::__throw_invalid_argument("plot not found !");
    }
}
