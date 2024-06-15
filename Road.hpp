#pragma once
#include "Point2D.hpp"


class Road {
private:
    Point2D start;
    Point2D end;


public:
    Road(Point2D start, Point2D end); 
    Point2D getStart() const;
    Point2D getEnd() const;
    bool operator==(const Road& other) const {
        return (start == other.start && end == other.end) || (start == other.end && end == other.start);
    }
};
