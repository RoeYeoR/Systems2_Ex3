#include "Board.hpp"
#include "Resource.hpp"
#include "PlotOfLand.hpp"

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
    // Define resources and piece names for each plot of land
    std::vector<Resource> resources = {
        Resource(ResourceType::Wood),
        Resource(ResourceType::Brick),
        Resource(ResourceType::Wool),
        Resource(ResourceType::Oat),
        Resource(ResourceType::Iron),
        Resource(ResourceType::None)  // Adding desert as None
    };
    std::vector<std::string> pieces = {"forest", "hills", "pasture land", "agricultural land", "mountains"};
    int resourceCount = resources.size();
    int plotCount = 19;


    // Assign resources, piece names, and numbers to plots
    for (int i = 0; i < plotCount; ++i) {
        PlotOfLand plot;
        plot.setlandType(pieces[i]);
        plot.setResource(resources[i % resourceCount].getType());
        plot.setNumber(rand() % 11 + 2); // Random number between 2 and 12
        plots.push_back(plot);
    }
}


PlotOfLand Board::getPlot(int index) const {
    if (index >= 0 && index < plots.size()) {
        return plots[index];
    }
    // Handle invalid index
    PlotOfLand emptyPlot;
    emptyPlot.setResource(ResourceType::None);
    emptyPlot.setNumber(0);
    return emptyPlot;
}
