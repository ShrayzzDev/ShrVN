#ifndef BEZIER_H
#define BEZIER_H

#include <vector>

struct Point;

// Calculate the Binomial coefficient
int Binomial(unsigned int N, unsigned int k);

Point CalculateOneBezierPoint(float CurveRatio, const std::vector<Point> & ArrayPoint);

std::vector<Point> CalculateAllBezierPoint (const std::vector<Point> & ControlPoint, int NbPoint);

#endif // BEZIER_H
