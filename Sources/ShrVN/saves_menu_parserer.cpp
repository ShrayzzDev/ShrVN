#include <filesystem>
#include <iostream>

#include "saves_menu_parserer.hpp"
#include "parserer_utils.h"

using namespace std;

SavesMenuParserer::SavesMenuParserer(ISaveMenuInterpretor * interpretor)
    :m_interpretor{interpretor}
{

}

SavesMenuParameters * SavesMenuParserer::ReadSavesMenuParametersFile(std::ifstream &file)
{
    unsigned long long nb_line = 1;
    int value;
    SavesMenuParameters *Parameters = new SavesMenuParameters();
    string word, temp, equal_sign, next_word, current_path;
    while (!file.eof())
    {
        if (filesystem::current_path().generic_string().ends_with("init"))
        {
            current_path = filesystem::current_path().generic_string() + "/..";
        }
        if (CheckEmptyLine(file))
        {
            ++nb_line;
            continue;
        }
        getline(file,word,' ');
        if (CheckComment(file,word))
        {
            ++nb_line;
            continue;
        }
        else if (word.starts_with("background_image"))
        {
            ReadStringVarAssignation(file,word,next_word);
            filesystem::path full_path = current_path + "/images/" + next_word;
            if (! filesystem::exists(full_path))
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid path.");
            }
            m_interpretor->SetBackgroundImage(*Parameters,next_word);
            ++nb_line;
            continue;
        }
        else if (word.starts_with("nb_pages"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 10 || value < 1)
            {
                goto wrong_argument;
            }
            m_interpretor->SetNbPages(*Parameters,value);
            ++nb_line;
            continue;
        }
        else if (word.starts_with("nb_saves"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 10 || value < 1)
            {
                goto wrong_argument;
            }
            m_interpretor->SetNbSavesPerPages(*Parameters,value);
            ++nb_line;
            continue;
        }
        else
        {
            goto unknown_keyword;
        }
    }
    return Parameters;
unknown_keyword:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + word + " ' in this context");

wrong_argument:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid argument ' " + word + " ' in this context");
}
