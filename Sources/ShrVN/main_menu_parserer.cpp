#include "main_menu_parserer.hpp"
#include "parserer_utils.h"

#include <filesystem>
#include <iostream>

using namespace std;

MainMenuParserer::MainMenuParserer(IMainMenuInterpretor * interpretor)
    : m_interpretor{interpretor}
{

}

MainMenuParameters *MainMenuParserer::ReadMainMenuParametersFile(std::ifstream &file)
{
    unsigned long long nb_line = 1;
    int value;
    MainMenuParameters *Parameters = new MainMenuParameters();
    string word, temp, equal_sign, next_word, current_path;
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
        if (word.starts_with("background_image"))
        {
            ReadStringVarAssignation(file,word,next_word);
            string full_path = current_path + "/images/" + next_word;
            cout << full_path << endl;
            if( !filesystem::exists(full_path))
            {
                goto wrong_argument;
            }
            m_interpretor->SetBackgroundImage(*Parameters,next_word);
            ++nb_line;
            continue;
        }
        else if (word.starts_with("logo"))
        {
            if (word.starts_with("logo_image"))
            {
                ReadStringVarAssignation(file,word,next_word);
                string full_path = current_path + "/images/" + next_word;
                cout << full_path << endl;
                if( !filesystem::exists(full_path))
                {
                    goto wrong_argument;
                }
                m_interpretor->SetLogoImg(*Parameters,next_word);
                ++nb_line;
                continue;
            }
            else if(word.starts_with("logo_xpos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetLogoXPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else if(word.starts_with("logo_ypos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1080)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetLogoYPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else
            {
                goto unknown_keyword;
            }
        }
        else if (word.starts_with("ng_btn"))
        {
            if (word.starts_with("ng_btn_xpos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetNewGameXPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else if (word.starts_with("ng_btn_ypos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1080)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetNewGameYPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else
            {
                goto unknown_keyword;
            }
        }
        else if (word.starts_with("credit_btn"))
        {
            if (word.starts_with("credit_btn_xpos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetCreditXPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else if (word.starts_with("credit_btn_ypos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1080)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetCreditYPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else
            {
                goto unknown_keyword;
            }
        }
        else if (word.starts_with("load_save"))
        {
            if (word.starts_with("load_save_xpos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetLoadSaveXPos(*Parameters,value);
                ++nb_line;
                continue;
            }
            else if (word.starts_with("load_save_ypos"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value < 0 || value > 1920)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetLoadSaveYPos(*Parameters,value);
                ++nb_line;
                continue;
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
    }
    return Parameters;
unknown_keyword:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + word + " ' in this context");

wrong_argument:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid argument ' " + word + " ' in this context");
}
