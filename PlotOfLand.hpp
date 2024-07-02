#ifndef PLOTOFLAND_HPP
#define PLOTOFLAND_HPP

#include "Resource.hpp"
#include "LandType.hpp"
#include "Point2D.hpp"
#include <string>
#include <vector>
#include <ostream>



class PlotOfLand {
private:
    Resource resource;
    LandType landType;
    int number;
    std::vector<Point2D> vertices;
    std::vector<Point2D> settlements;

public:
    PlotOfLand();
    PlotOfLand(ResourceType type, int num);
    void setResource(ResourceType type);
    void setNumber(int num);
    void setlandType(LandType landType);
    LandType getlandType();
    Resource getResource() const;
    int getNumber() const;
    LandType getLandType() const;
    std::vector<Point2D> getVertices();
    void setUpVertex(Point2D p);
    void setUpRightVertex(Point2D p);
    void setBottomRightVertex(Point2D p);
    void setBottomVertex(Point2D p);
    void setBottomLeftVertex(Point2D p);
    void setUpLeftVertex(Point2D p);
    Point2D getUpVertex();
    Point2D getUpRightVertex();
    Point2D getBottomRightVertex();
    Point2D getBottomVertex();
    Point2D getBottomLeftVertex();
    Point2D getUpLeftVertex();
    void printVertices() const;
    bool hasSettlementAtVertex(const Point2D& vertex) const;
    void addSettlement(const Point2D& vertex);
    friend std::ostream& operator<< (std::ostream& os,PlotOfLand pol); 
   
};

#endif // PLOTOFLAND_HPP
