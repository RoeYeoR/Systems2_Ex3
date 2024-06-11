#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "Resource.hpp"
#include "PlotOfLand.hpp"




class Board {

private: 
     std::vector<PlotOfLand> plots;



public:
    Board();
    void initializeBoard();
    PlotOfLand getPlot(int index) const;
};

#endif // BOARD_HPP
