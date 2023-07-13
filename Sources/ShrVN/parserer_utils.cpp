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

bool CheckEmptyLine(std::ifstream &file)
{
    if ((char)file.peek() == '\n')
    {
        file.get();
        return true;
    }
    return false;
}

bool CheckComment(std::ifstream & file, const std::string & word)
{
    string temp;
    if (word.starts_with("//"))
    {
        getline(file, temp, '\n');
        return true;
    }
    return false;
}
