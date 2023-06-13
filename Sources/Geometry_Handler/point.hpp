#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

struct Point
{
    int m_x;
    int m_y;
};

std::ostream & operator<<(std::ostream & os, Point Pt);

Point MultiplyCoefPoint(float Coef, Point Pt);

Point operator*(float Coef, Point Pt);

Point operator*(Point Pt, float Coef);

Point operator+(Point Pt1, Point Pt2);

#endif // POINT_HPP
