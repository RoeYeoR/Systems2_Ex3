#pragma once


class Point2D
{
private:
    int x;
    int y;

public:
    Point2D();
    Point2D(int x,int y);
    int getX()const;
    int getY()const;
    bool operator==(const Point2D& other) const;
    double distanceTo(const Point2D& other) const;

};