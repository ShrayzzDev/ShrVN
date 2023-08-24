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
    getline(file,result);
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
    std::string temp;
    if ((char)file.peek() == '\n' || (char)file.peek() == '\r')
    {
        getline(file,temp);
        return true;
    }
    return false;
}

bool CheckComment(std::ifstream & file, const std::string & word)
{
    string temp;
    if (word.starts_with("//"))
    {
        getline(file, temp);
        return true;
    }
    return false;
}

bool IsOnlyWhiteSpaces(const string & word)
{
    for (auto chr : word)
    {
        if (!isspace(chr))
        {
            return false;
        }
    }
    return true;
}

string GetSaveDataFolder(const std::string & project_name)
{
    std::string save_folder;
#ifdef _WIN64
    save_folder = getenv("appdata");
    save_folder += "/../Local/" + project_name;
#elif __linux__
    save_folder = getenv("HOME");
    save_folder += "/." + project_name;
#endif
    return save_folder;
}
