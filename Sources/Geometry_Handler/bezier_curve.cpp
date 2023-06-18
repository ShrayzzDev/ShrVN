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
// ControlPoint = An array on Point
Point CalculateOneBezierPoint(float CurveRatio, const vector<Point> & ControlPoint)
{
    Point CurvePoint = {0,0};
    unsigned short CurveOrder = ControlPoint.size() - 1;
    for (unsigned short k = 0; k < ControlPoint.size() ; ++k)
    {
        CurvePoint = CurvePoint + Binomial(CurveOrder,k)*(pow(CurveRatio,k))*pow((1-CurveRatio),CurveOrder - k) * ControlPoint[k];
    }
    return CurvePoint;
}

vector<Point> CalculateAllBezierPoint (const vector<Point> & ControlPoint, int NbPoint)
{
    vector<Point> CurvePoints;
    CurvePoints.push_back(ControlPoint.front());
    float TempRatio = (1.0 / NbPoint);
    for (int rep = 1; rep <= NbPoint; ++rep)
    {
        float Ratio = rep * TempRatio;
        cout << "Ratio : " << Ratio << endl;
        CurvePoints.push_back(CalculateOneBezierPoint(Ratio,ControlPoint));
    }
    return CurvePoints;
}
