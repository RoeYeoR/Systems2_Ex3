//315144972
//roeyshmil09@gmail.com

#include "Point2D.hpp"
#include <cmath>


Point2D::Point2D(){};
Point2D::Point2D(int x, int y) : x(x) , y(y) {}

int Point2D::getX() const
{
return this->x;
}

int Point2D::getY() const
{
return this->y;
}


bool Point2D::operator==(const Point2D& other) const {
    return (x == other.x && y == other.y);
}

double Point2D::distanceTo(const Point2D& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}    