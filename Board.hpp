#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include <vector>
#include "Resource.hpp"
#include "PlotOfLand.hpp"




class Board {

private:
    std::vector<std::vector<int>> layout;
    std::vector<PlotOfLand> plots;
    std::vector<std::vector<int>> positions;
    std::vector<Point2D> globalSettlements; 


public:
    Board();
    void printBoard();
    void printLayout();
    void initializeBoard();
    std::vector<PlotOfLand> getPlots();
    void setPlotsVertices();
    void addSettlement(int plotIndex, const Point2D& vertex);
    bool isVertexOccupied(const Point2D& vertex) const;
    PlotOfLand getPlot(int index) const;
};

#endif // BOARD_HPP
