#include <iostream>
#include <vector>
#include <filesystem>

#include "point.hpp"
#include "bezier.h"
#include "characters.hpp"
#include "parserer.h"

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
    Point Pt1 = {100,200}, Pt2 = {100,400};
    vector<Point> CurvePoint = {Pt1,Pt2};
    for (Point Pt : CurvePoint)
    {
        cout << Pt << endl;
    }
    cout << "Premier Point: " << CalculateOneBezierPoint(0,CurvePoint) << endl;
    cout << "Milieu Point: " << CalculateOneBezierPoint(0.5,CurvePoint) << endl;
    cout << "Dernier Point: " << CalculateOneBezierPoint(1,CurvePoint) << endl;
    Point Pt3 = {200,500};
    CurvePoint.push_back(Pt3);
    cout << "Ajout de Pt3" << endl;
    cout << CalculateAllBezierPoint(CurvePoint,5) << endl;
}

void ShowCharNameColors(const Characters & chr)
{
    cout << "Rouge: " << chr.GetRedValue() << endl;
    cout << "Vert: " << chr.GetGreenValue() << endl;
    cout << "Bleu: " << chr.GetBlueValue() << endl;
    for (int i = 0; i < 50 ; ++i)
        cout << "-" ;
}

void TestCharcters()
{
    filesystem::current_path(filesystem::path("../Scripts/ScriptTest"));
    Characters chr1 = {"Jean"};
    cout << chr1.GetName() << endl;
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Changing the red value to 150" << endl;
    try
    {
        chr1.SetRedValue(150);
    }
    catch(const exception & e)
    {
        cerr << e.what() << endl;
    }
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Setting the red value to 999" << endl;
    try
    {
        chr1.SetRedValue(999);
    }
    catch(const exception & e)
    {
        cerr << e.what() << endl;
    }
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Getting the image 'aaaa' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("aaaa") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Adding the image 'bed.webp' to " << chr1.GetName() << endl;
    chr1.AddImage("bed","bed.webp");
    cout << "Getting thte image 'bed.webp' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("bed") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Adding a 'default' image to " << chr1.GetName() << endl;
    chr1.AddImage("default","Akane.png");
    cout << "Getting the default image." << endl << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("default") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Getting the image 'aaaa' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("aaaa") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
}

void TestCharParserer()
{
    filesystem::current_path(filesystem::path("../Scripts/ScriptTest"));
    map<string, Characters>& Characters_map = *ParseCharacterFile();
    cout << Characters_map.at("Jean").GetName() << endl;
    cout << Characters_map.at("Jean").GetBlueValue() << endl;
    cout << Characters_map.at("Jean2").GetName() << endl;
    cout << Characters_map.at("Jean2").GetBlueValue() << endl;
    cout << Characters_map.at("Jean2").GetGreenValue() << endl;
    cout << Characters_map.at("Jean2").GetRedValue() << endl;
}

int main()
{
    TestCharParserer();
    return 0;
}
