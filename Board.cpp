#include "Board.hpp"
#include "Resource.hpp"
#include "PlotOfLand.hpp"
#include <random>
#include "../../../../../../usr/include/c++/11/bits/algorithmfwd.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Point2D.hpp"

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
    std::shuffle(numbers.begin(), numbers.end(), g);

    int plotCount = 19;

    // Create plots and explicitly set the desert at position 9
    std::vector<PlotOfLand> plots(plotCount);
    for (int i = 0; i < plotCount; ++i) {
        plots[i] = PlotOfLand();
    }

    plots[9].setlandType(LandType::Desert);
    plots[9].setResource(ResourceType::None);
    plots[9].setNumber(0);

    int resourceIndex = 0;
    int landTypeIndex = 0;
    int numberIndex = numbers.size() - 1;

    for (int i = 0; i < plotCount; ++i) {
        if (i == 9) {
            continue;
        }

        plots[i].setlandType(land_Types[landTypeIndex++]);
        plots[i].setResource(resources[resourceIndex++].getType());

        if (plots[i].getlandType() == LandType::Desert) {
            plots[i].setNumber(0);
        } else {
            plots[i].setNumber(numbers[numberIndex--]);
        }
    }

    this->plots = plots;

    setPlotsVertices();
}

void Board::printBoard() {
    // Define the layout of the board
    std::vector<std::vector<int>> layout = {
        {0, 1, 2},
        {3, 4, 5, 6},
        {7, 8, 9, 10, 11},
        {12, 13, 14, 15},
        {16, 17, 18}
    };

    std::cout << "||||||||||||||||||||||||------CATAN BOARD-----|||||||||||||||||||||||||||||||||||||" << "\n" <<"\n";

    // Print the board
    for (const auto& row : layout) {
        std::cout << std::setw(6 * (5 - row.size())) << ""; // Adjust spacing for center alignment
        for (const auto& plotIndex : row) {
            const auto& plot = plots[plotIndex];
            std::cout << plot.getLandType() << "(" << plot.getNumber() << ")    ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
        std::cout << std::endl;
        std::cout <<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" <<"\n" "\n";

}


void Board::setPlotsVertices()
{
    plots[0].setUpVertex(Point2D(0,3));
    plots[0].setUpRightVertex(Point2D(1,4));
    plots[0].setBottomRightVertex(Point2D(2,4));
    plots[0].setBottomVertex(Point2D(3,3));
    plots[0].setBottomLeftVertex(Point2D(2,2));
    plots[0].setUpLeftVertex(Point2D(1,2));

    plots[1].setUpVertex(Point2D(0,5));
    plots[1].setUpRightVertex(Point2D(1,6));
    plots[1].setBottomRightVertex(Point2D(2,6));
    plots[1].setBottomVertex(Point2D(3,5));
    plots[1].setBottomLeftVertex(Point2D(2,4));
    plots[1].setUpLeftVertex(Point2D(1,4));

    plots[2].setUpVertex(Point2D(0,7));
    plots[2].setUpRightVertex(Point2D(1,8));
    plots[2].setBottomRightVertex(Point2D(2,8));
    plots[2].setBottomVertex(Point2D(3,7));
    plots[2].setBottomLeftVertex(Point2D(2,6));
    plots[2].setUpLeftVertex(Point2D(1,6));

    plots[3].setUpVertex(Point2D(2,2));
    plots[3].setUpRightVertex(Point2D(3,3));
    plots[3].setBottomRightVertex(Point2D(4,3));
    plots[3].setBottomVertex(Point2D(5,2));
    plots[3].setBottomLeftVertex(Point2D(4,1));
    plots[3].setUpLeftVertex(Point2D(3,1));

    plots[4].setUpVertex(Point2D(2,4));
    plots[4].setUpRightVertex(Point2D(3,5));
    plots[4].setBottomRightVertex(Point2D(4,5));
    plots[4].setBottomVertex(Point2D(5,4));
    plots[4].setBottomLeftVertex(Point2D(4,3));
    plots[4].setUpLeftVertex(Point2D(3,3));

    plots[5].setUpVertex(Point2D(2,6));
    plots[5].setUpRightVertex(Point2D(3,7));
    plots[5].setBottomRightVertex(Point2D(4,7));
    plots[5].setBottomVertex(Point2D(5,6));
    plots[5].setBottomLeftVertex(Point2D(4,5));
    plots[5].setUpLeftVertex(Point2D(3,5));

    plots[6].setUpVertex(Point2D(2,8));
    plots[6].setUpRightVertex(Point2D(3,9));
    plots[6].setBottomRightVertex(Point2D(4,9));
    plots[6].setBottomVertex(Point2D(5,8));
    plots[6].setBottomLeftVertex(Point2D(4,7));
    plots[6].setUpLeftVertex(Point2D(3,7));

    plots[7].setUpVertex(Point2D(4,1));
    plots[7].setUpRightVertex(Point2D(5,2));
    plots[7].setBottomRightVertex(Point2D(6,2));
    plots[7].setBottomVertex(Point2D(7,1));
    plots[7].setBottomLeftVertex(Point2D(6,0));
    plots[7].setUpLeftVertex(Point2D(5,0));

    plots[8].setUpVertex(Point2D(4,3));
    plots[8].setUpRightVertex(Point2D(5,4));
    plots[8].setBottomRightVertex(Point2D(6,4));
    plots[8].setBottomVertex(Point2D(7,3));
    plots[8].setBottomLeftVertex(Point2D(6,2));
    plots[8].setUpLeftVertex(Point2D(5,2));

    plots[9].setUpVertex(Point2D(4,5));
    plots[9].setUpRightVertex(Point2D(5,6));
    plots[9].setBottomRightVertex(Point2D(6,6));
    plots[9].setBottomVertex(Point2D(7,5));
    plots[9].setBottomLeftVertex(Point2D(6,4));
    plots[9].setUpLeftVertex(Point2D(5,4));

    plots[10].setUpVertex(Point2D(4,7));
    plots[10].setUpRightVertex(Point2D(5,8));
    plots[10].setBottomRightVertex(Point2D(6,8));
    plots[10].setBottomVertex(Point2D(7,7));
    plots[10].setBottomLeftVertex(Point2D(6,6));
    plots[10].setUpLeftVertex(Point2D(5,6));

    plots[11].setUpVertex(Point2D(4,9));
    plots[11].setUpRightVertex(Point2D(5,10));
    plots[11].setBottomRightVertex(Point2D(6,10));
    plots[11].setBottomVertex(Point2D(7,9));
    plots[11].setBottomLeftVertex(Point2D(6,8));
    plots[11].setUpLeftVertex(Point2D(5,8));

    plots[12].setUpVertex(Point2D(6,2));
    plots[12].setUpRightVertex(Point2D(7,3));
    plots[12].setBottomRightVertex(Point2D(8,3));
    plots[12].setBottomVertex(Point2D(9,2));
    plots[12].setBottomLeftVertex(Point2D(8,1));
    plots[12].setUpLeftVertex(Point2D(7,1));

    plots[13].setUpVertex(Point2D(6,4));
    plots[13].setUpRightVertex(Point2D(7,5));
    plots[13].setBottomRightVertex(Point2D(8,5));
    plots[13].setBottomVertex(Point2D(9,4));
    plots[13].setBottomLeftVertex(Point2D(8,3));
    plots[13].setUpLeftVertex(Point2D(7,3));

    plots[14].setUpVertex(Point2D(6,6));
    plots[14].setUpRightVertex(Point2D(7,7));
    plots[14].setBottomRightVertex(Point2D(8,7));
    plots[14].setBottomVertex(Point2D(9,6));
    plots[14].setBottomLeftVertex(Point2D(8,5));
    plots[14].setUpLeftVertex(Point2D(7,5));

    plots[15].setUpVertex(Point2D(6,8));
    plots[15].setUpRightVertex(Point2D(7,9));
    plots[15].setBottomRightVertex(Point2D(8,9));
    plots[15].setBottomVertex(Point2D(9,8));
    plots[15].setBottomLeftVertex(Point2D(8,7));
    plots[15].setUpLeftVertex(Point2D(7,7));

    plots[16].setUpVertex(Point2D(8,3));
    plots[16].setUpRightVertex(Point2D(9,4));
    plots[16].setBottomRightVertex(Point2D(10,4));
    plots[16].setBottomVertex(Point2D(11,3));
    plots[16].setBottomLeftVertex(Point2D(10,2));
    plots[16].setUpLeftVertex(Point2D(9,2));

    plots[17].setUpVertex(Point2D(8,5));
    plots[17].setUpRightVertex(Point2D(9,6));
    plots[17].setBottomRightVertex(Point2D(10,6));
    plots[17].setBottomVertex(Point2D(11,5));
    plots[17].setBottomLeftVertex(Point2D(10,4));
    plots[17].setUpLeftVertex(Point2D(9,4));

    plots[18].setUpVertex(Point2D(8,7));
    plots[18].setUpRightVertex(Point2D(9,8));
    plots[18].setBottomRightVertex(Point2D(10,8));
    plots[18].setBottomVertex(Point2D(11,7));
    plots[18].setBottomLeftVertex(Point2D(10,6));
    plots[18].setUpLeftVertex(Point2D(9,6));

}






PlotOfLand Board::getPlot(int index) const {
    if (index >= 0 && index < plots.size()) {
        return plots[index];
    }
    else{
        std::__throw_invalid_argument("plot not found !");
    }
}
