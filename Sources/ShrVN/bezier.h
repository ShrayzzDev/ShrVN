#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

struct Point;

// Calculate the Binomial coefficient
int Binomial(unsigned int N, unsigned int k);

// CurveRatio = Ratio to tell the function which point to calculate (from 0 to 1)
// ControlPoint = An array of the points that control the curve
Point CalculateOneBezierPoint(float CurveRatio, const std::vector<Point> & ControlPoint);

// ControlPoint = An array of the points that control the curve
// NbPoint = Number of point the final curve will have
std::vector<Point> CalculateAllBezierPoint (const std::vector<Point> & ControlPoint, unsigned int NbPoint);

#endif // BEZIER_H
