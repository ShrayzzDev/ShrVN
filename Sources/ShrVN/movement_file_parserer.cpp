#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cctype>

#include "movement_file_parserer.h"
#include "parserer_utils.h"

using namespace std;

MovementFileParserer::MovementFileParserer(IMovementFileInterpretor *interpretor)
    :m_interpretor{interpretor}
{

}

map<string,Movement> * MovementFileParserer::FileParserer(ifstream & file)
{
    map<string,Movement> * map = new ::map<string,Movement>();
    string mvt_name, value, unread_mvt;
    unsigned short x_value, y_value;
    while (!file.eof())
    {
        vector<Point> new_mvt;
        if (CheckEmptyLine(file))
        {
            continue;
        }
        getline(file,mvt_name,'{');
        if (CheckComment(file,mvt_name))
        {
            continue;
        }
        while(find(mvt_name.begin(),mvt_name.end(),' ') != mvt_name.end())
        {
            mvt_name.erase(find(mvt_name.begin(),mvt_name.end(),' '));
        }
        while(find(mvt_name.begin(),mvt_name.end(),'\n') != mvt_name.end())
        {
            mvt_name.erase(find(mvt_name.begin(),mvt_name.end(),'\n'));
        }
        getline(file,unread_mvt,'}');
        stringstream ss(unread_mvt);
        while (!ss.eof())
        {
            getline(ss,value,',');
            if (IsOnlyWhiteSpaces(value))
            {
                break;
            }
            x_value = stoi(value);
            getline(ss,value,'\n');
            if (IsOnlyWhiteSpaces(value))
            {
                break;
            }
            y_value = stoi(value);
            Point pt = {x_value,y_value};
            new_mvt.push_back(pt);
        }
        m_interpretor->CreateMovement(*map,new_mvt,mvt_name);
    }
    return map;
}
