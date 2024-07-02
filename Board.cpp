//315144972
//roeyshmil09@gmail.com

#include "Board.hpp"
#include "Resource.hpp"
#include "PlotOfLand.hpp"
#include <unordered_map>
#include <random>
#include "../../../../../../usr/include/c++/11/bits/algorithmfwd.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Point2D.hpp"


Board::Board() : positions(12, std::vector<int>(11)) {
initializeBoard();

layout = {{0, 1, 2},
    {3, 4, 5, 6},
    {7, 8, 9, 10, 11},
    {12, 13, 14, 15},
    {16, 17, 18}};
}

std::vector<PlotOfLand> Board::getPlots()
{
return plots;
}

void Board::initializeBoard() {
    // Define the possible land types and their distribution
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

std::vector<int> numbers = {
    2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
};

// Initialize random seed
std::random_device rd;
std::mt19937 g(rd());

// Shuffle the land types and numbers
std::shuffle(land_Types.begin(), land_Types.end(), g);
std::shuffle(numbers.begin(), numbers.end(), g);

int plotCount = 19;

// Create plots and explicitly set the desert at a random position
std::vector<PlotOfLand> plots(plotCount);
for (int i = 0; i < plotCount; ++i) {
    plots[i] = PlotOfLand();
}

// LandType to ResourceType mapping
std::unordered_map<LandType, ResourceType> landToResourceMap = {
    { LandType::Forest, ResourceType::Wood },
    { LandType::Hills, ResourceType::Brick },
    { LandType::PastureLand, ResourceType::Wool },
    { LandType::AgriculturalLand, ResourceType::Oat },
    { LandType::Mountains, ResourceType::Iron },
    { LandType::Desert, ResourceType::None }
};

// Find a random position for the desert
int desertIndex = std::uniform_int_distribution<int>(0, plotCount - 1)(g);

// Set plots properties based on shuffled vectors
int landTypeIndex = 0;
int numberIndex = numbers.size() - 1;

for (int i = 0; i < plotCount; ++i) {
    if (i == desertIndex) {
        plots[i].setlandType(LandType::Desert);
        plots[i].setResource(ResourceType::None);
        plots[i].setNumber(0);
    } else {
        plots[i].setlandType(land_Types[landTypeIndex]);
        plots[i].setResource(landToResourceMap[land_Types[landTypeIndex]]);

        if (land_Types[landTypeIndex] == LandType::Desert) {
            plots[i].setNumber(0);
        } else {
            plots[i].setNumber(numbers[numberIndex--]);
        }

        ++landTypeIndex;
    }
}

this->plots = plots;

setPlotsVertices();
}


void Board::addSettlement(int plotIndex, const Point2D& vertex) {
    plots[plotIndex].addSettlement(vertex);
    globalSettlements.push_back(vertex);
}

    bool Board::isVertexOccupied(const Point2D& vertex) const {
    for (const auto& settlement : globalSettlements) {
        if (settlement == vertex) {
            return true;
        }
    }
    return false;
}


void Board::printBoard() {

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

void Board::printLayout()
{
std::vector<std::vector<int>> layout = 
{
    {0, 1, 2, -1, -1},
    {3, 4, 5, 6, -1},
    {7, 8, 9, 10, 11},
    {12, 13, 14, 15, -1},
    {16, 17, 18, -1, -1}
};

std::cout<<"          Layout: "<<"\n";

for (int i = 0; i < 5; ++i) {
    // Print leading spaces based on the row number
    std::cout << std::setw((4 - i) * 2) << ""; // Adjust the multiplier to match the desired spacing
    
    for (int j = 0; j < 5; ++j) {
        if (layout[i][j] != -1) {
            std::cout << layout[i][j] << " ";
        }
    }
    std::cout << std::endl;
}

std::cout << std::endl;
std::cout <<"*****************************************************************************************************" <<std::endl;


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
