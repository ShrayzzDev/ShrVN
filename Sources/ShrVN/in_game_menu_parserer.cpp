#include <filesystem>

#include "in_game_menu_parserer.hpp"
#include "parserer_utils.h"

using namespace std;

InGameMenuParserer::InGameMenuParserer(IInGameMenuInterpretor * interpretor)
    :m_interpretor{interpretor}
{

}

InGameMenuParameters * InGameMenuParserer::ReadInGameMenuParametersFile(std::ifstream & file)
{
    unsigned long long nb_line = 1;
    int value;
    InGameMenuParameters * Parameters = new InGameMenuParameters();
    string word, temp, next_word, current_path;
    if (filesystem::current_path().generic_string().ends_with("init"))
    {
        current_path = filesystem::current_path().generic_string() + "/..";
    }
    while (!file.eof())
    {
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
        else if (word.starts_with("background_img"))
        {
            if (word.starts_with("background_img_path"))
            {
                ReadStringVarAssignation(file,word,next_word);
                string full_path = current_path + "/images/" + next_word;
                if( !filesystem::exists(full_path))
                {
                    goto wrong_argument;
                }
                m_interpretor->SetBackgroundImage(*Parameters,next_word);
            }
            else if (word.starts_with("background_img_opacity"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 255)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetBgImgOpacity(*Parameters,value);
            }
            else
            {
                goto unknown_keyword;
            }
        }
        else if (word.starts_with("save_icon"))
        {
            ReadStringVarAssignation(file,word,next_word);
            string full_path = current_path + "/images/" + next_word;
            if( !filesystem::exists(full_path))
            {
                goto wrong_argument;
            }
            m_interpretor->SetSaveIcon(*Parameters,next_word);
        }
        else if (word.starts_with("option_icon"))
        {
            ReadStringVarAssignation(file,word,next_word);
            string full_path = current_path + "/images/" + next_word;
            if( !filesystem::exists(full_path))
            {
                goto wrong_argument;
            }
            m_interpretor->SetOptionIcon(*Parameters,next_word);
        }
        else if (word.starts_with("title_menu_icon"))
        {
            ReadStringVarAssignation(file,word,next_word);
            string full_path = current_path + "/images/" + next_word;
            if( !filesystem::exists(full_path))
            {
                goto wrong_argument;
            }
            m_interpretor->SetTitleMenuIcon(*Parameters,next_word);
        }
        else if (word.starts_with("btn"))
        {
            if (word.starts_with("btn_height"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetBtnHeight(*Parameters,value);
            }
            else if (word.starts_with("btn_length"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1080)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetBtnLength(*Parameters,value);
            }
            else
            {
                goto unknown_keyword;
            }
        }
        else
        {
            goto unknown_keyword;
        }
        ++nb_line;
    }
    return Parameters;
unknown_keyword:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + word + " ' in this context");

wrong_argument:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid argument ' " + word + " ' in this context");
}
