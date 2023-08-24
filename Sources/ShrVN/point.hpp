#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>
#include <list>
#include <vector>
// A point is only defined by it's X and Y coordinate.
// WARNING : the coordinates are int for operations to be faster
// WARNING : and so, point WON'T store floats, as their main use
// WARNING : are gonna be with screens (and you can't show half a pixel)
struct Point
{
    int m_x;
    int m_y;
};

// Function that multiply a point with a coefficient.
// Used by the overloaded operator *
Point MultiplyCoefPoint(float Coef, Point Pt);

// Overload to create a stream with one point
std::ostream & operator<<(std::ostream & os, Point Pt);

// Overload to create a stream with a list of point.
std::ostream & operator<<(std::ostream & os, std::list<Point> Pts);

// Overload to create a stream with a vector of point.
std::ostream & operator<<(std::ostream & os, std::vector<Point> Pts);

// Compares the coordinates
bool operator==(Point pt1, Point pt2);

// Overloads of the operator * for it to work in both ways
Point operator*(float Coef, Point Pt);

Point operator*(Point Pt, float Coef);

//Overload the operator + to add points.
Point operator+(Point Pt1, Point Pt2);

#endif // POINT_HPP
