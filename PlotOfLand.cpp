//315144972
//roeyshmil09@gmail.com

#include "PlotOfLand.hpp"
#include <string>
#include <map>
#include "Board.hpp"

PlotOfLand::PlotOfLand() : resource(ResourceType::None), landType(LandType::Desert), number(0), vertices(6) {}

PlotOfLand::PlotOfLand(ResourceType type, int num) : resource(type), number(num) ,vertices(6) {}

void PlotOfLand::setResource(ResourceType type) {
    this->resource = Resource(type);
}

void PlotOfLand::setNumber(int num) {
    this->number = num;
}

void PlotOfLand::setlandType(LandType landType)
{
    this->landType = landType;

}

LandType PlotOfLand::getlandType()
{
    return this->landType;
}

Resource PlotOfLand::getResource() const {
    return resource;
}

int PlotOfLand::getNumber() const {
    return number;
}

LandType PlotOfLand::getLandType() const {
    return this->landType;
}

 std::vector<Point2D> PlotOfLand::getVertices()
 {
    return vertices;
 }

Point2D PlotOfLand::getUpVertex()
{
    return vertices[0];

}

 Point2D PlotOfLand::getUpRightVertex()
 {
    return vertices[1];

 }

 Point2D PlotOfLand::getBottomRightVertex()
 {
    return vertices[2];

 }

Point2D PlotOfLand::getBottomVertex()
{
    return vertices[3];


}
Point2D PlotOfLand::getBottomLeftVertex()
{
    return vertices[4];

}


Point2D PlotOfLand::getUpLeftVertex()
{
    return vertices[5];

}

void PlotOfLand::setUpVertex(Point2D p)
{
     vertices[0] = p;

}
void PlotOfLand::setUpRightVertex(Point2D p)
{
    vertices[1] = p;

}
void PlotOfLand::setBottomRightVertex(Point2D p)
{
      vertices[2] = p;
}
void PlotOfLand::setBottomVertex(Point2D p)
{
     vertices[3] = p;

}
void PlotOfLand::setBottomLeftVertex(Point2D p)
{
    vertices[4] = p;

}
void PlotOfLand::setUpLeftVertex(Point2D p)
{
      vertices[5] = p;

}

// Check if a given vertex has a settlement
bool PlotOfLand::hasSettlementAtVertex(const Point2D& vertex) const {
    for (const auto& settlement : settlements) {
        if (settlement == vertex) {
            return true;
        }
    }
    return false;
}

 // Add a settlement at a given vertex
    void PlotOfLand::addSettlement(const Point2D& vertex) {
        if (hasSettlementAtVertex(vertex)) {
            throw std::invalid_argument("Vertex already has a settlement.");
        }
        settlements.push_back(vertex);
    }

void PlotOfLand::printVertices() const {
    std::cout << "Vertices of plot: ";
    for (const auto& vertex : vertices) {
        std::cout << "(" << vertex.getX() << ", " << vertex.getY() << ") ";
    }
    std::cout << std::endl;
}



std::ostream & operator<<(std::ostream &os, PlotOfLand pol)
{
    os<< "Land Type: " << pol.getLandType() << "\n";
    os<< "Number: "<< pol.getNumber() << "\n";
    return os;
}
