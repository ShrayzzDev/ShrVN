#include <iostream>
#include <vector>
#include <cmath>

#include "point.hpp"
#include "bezier.h"

using namespace std;

int Binomial(unsigned int N, unsigned int k)
{
    if(k>(N-k))
        k=N-k;

    int result=1;
    for(unsigned int i = 0; i < k; ++i){
        result *= (N-i);
        result /= (i+1);
    }
    return result;
}

// CurveRatio = Ratio to tell the function which point to calculate (from 0 to 1)
// ArrayPoint = An array on Point
Point CalculateOneBezierPoint(float CurveRatio, const vector<Point> & ArrayPoint)
{
    Point CurvePoint = {0,0};
    unsigned short CurveOrder = ArrayPoint.size() - 1;
    for (unsigned short k = 0; k < ArrayPoint.size() ; ++k)
    {
        CurvePoint = CurvePoint + Binomial(CurveOrder,k)*(pow(CurveRatio,k))*pow((1-CurveRatio),CurveOrder - k) * ArrayPoint[k];
    }
    return CurvePoint;
}
