#include "point.hpp"

std::ostream & operator<<(std::ostream & os, Point Pt)
{
    return os << "X: " << Pt.m_x << " Y: " << Pt.m_y;
}

std::ostream & operator<<(std::ostream & os, std::list<Point> Pts)
{
    for (Point Pt : Pts)
    {
        os << Pt << std::endl;
    }
    return os;
}

std::ostream & operator<<(std::ostream & os, std::vector<Point> Pts)
{
    for (Point pt : Pts)
    {
        os << pt << std::endl;
    }
    return os;
}

Point MultiplyCoefPoint(float Coef, Point Pt)
{
    Point temp;
    temp.m_x = Coef * Pt.m_x;
    temp.m_y = Coef * Pt.m_y;
    return temp;
}

Point operator*(float Coef, Point Pt)
{
    return MultiplyCoefPoint(Coef,Pt);
}

Point operator*(Point Pt, float Coef)
{
    return MultiplyCoefPoint(Coef,Pt);
}

Point operator+(Point Pt1, Point Pt2)
{
    Point temp;
    temp.m_x = Pt1.m_x + Pt2.m_x;
    temp.m_y = Pt1.m_y + Pt2.m_y;
    return temp;
}
