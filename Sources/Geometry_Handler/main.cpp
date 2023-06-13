#include <iostream>
#include <vector>

#include "point.hpp"
#include "bezier.h"

using namespace std;

void TestBinomial()
{
    int ArrayN[5] = {1,3,5,6,8};
    int ArrayK[5] = {1,4,7,9,10};
    for (int n : ArrayN)
    {
        for (int k : ArrayK)
        {
            int temp_binom = Binomial(n,k);
            if (temp_binom > 0)
            {
                cout << "Binomial avec n = " << n << " et k = " << k << " : " << temp_binom << endl;
            }
        }
    }
}

void TestBezier()
{
    Point Pt1 = {1,2}, Pt2 = {1,4};
    vector<Point> CurvePoint = {Pt1,Pt2};
    for (Point Pt : CurvePoint)
    {
        cout << Pt << endl;
    }
    cout << "Premier Point: " << CalculateOneBezierPoint(0,CurvePoint) << endl;
    cout << "Milieu Point: " << CalculateOneBezierPoint(0.5,CurvePoint) << endl;
    cout << "Dernier Point: " << CalculateOneBezierPoint(1,CurvePoint) << endl;
}

int main()
{
    TestBezier();
    return 0;
}
