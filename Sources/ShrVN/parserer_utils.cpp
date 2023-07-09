#include "parserer_utils.h"

using namespace std;

void ReadStringVarAssignation(ifstream & file, const string & word, string & result)
{
    string temp;
    if (word.back() != '=')
    {
        getline(file,temp,'=');
    }
    while((char)file.peek() == ' ')
    {
        file.get();
    }
    getline(file, result, '\n');
    return;
}

void ReadIntVarAssignation(ifstream & file, const string & word, int & result)
{
    string value;
    ReadStringVarAssignation(file,word,value);
    result = stof(value);
}
