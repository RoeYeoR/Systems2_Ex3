//315144972
//roeyshmil09@gmail.com

#include "Road.hpp"
#include "Point2D.hpp"

 Road::Road(Point2D start, Point2D end) : start(start), end(end) {}

 Point2D Road::getStart() const
 {
    return start;
 }

 Point2D Road::getEnd() const
 {
    return end;
 }