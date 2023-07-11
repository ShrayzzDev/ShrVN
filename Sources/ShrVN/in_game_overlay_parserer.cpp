#include <string>
#include <fstream>

#include "in_game_overlay_parserer.hpp"
#include "parserer_utils.h"

using namespace std;

InGameOverlayParserer::InGameOverlayParserer(IInGameOverlayInterpretor * interpretor)
    : m_interpretor{interpretor}
{

}

InGameOverlayParameters * InGameOverlayParserer::ReadInGameOverlayParametersFile(ifstream & file)
{
    unsigned long long nb_line = 1;
    int value;
    InGameOverlayParameters *Parameters = new InGameOverlayParameters();
    string word, temp, equal_sign, next_word;
    while (!file.eof())
    {
        if ((char)file.peek() == '\n')
        {
            file.get();
            continue;
        }
        getline(file,word,' ');
        if (word.starts_with("//"))
        {
            getline(file, temp, '\n');
            ++nb_line;
            continue;
        }
        else if (word.starts_with("text_mode"))
        {
            ReadStringVarAssignation(file,word,next_word);
            if (next_word == "ADV")
            {
                m_interpretor->SetTextMode(*Parameters,ADV);
            }
            else if (next_word == "NVL")
            {
                m_interpretor->SetTextMode(*Parameters,NVL);;
            }
            else
            {
                goto wrong_argument;
            }
            ++nb_line;
            continue;
        }
        else if (word.starts_with("in_game_option_position"))
        {
            ReadStringVarAssignation(file,word,next_word);
            if (next_word == "inside_bottom")
            {
                m_interpretor->SetInGameOptionPosition(*Parameters,inside_bottom);
            }
            else if (next_word == "outside_right")
            {
                m_interpretor->SetInGameOptionPosition(*Parameters,outside_right);
            }
            else if (next_word == "outside_left")
            {
                m_interpretor->SetInGameOptionPosition(*Parameters,inside_bottom);
            }
            else
            {
                goto wrong_argument;
            }
            ++nb_line;
            continue;
        }
        else if (word.starts_with("main_block_"))
        {
            if (word.starts_with("main_block_shape"))
            {
                ReadStringVarAssignation(file,word,next_word);
                if (next_word == "base_rectangle")
                {
                    m_interpretor->SetTextBlockShape(*Parameters,base_rectangle);
                }
                else if (next_word == "fading_rectangle")
                {
                    m_interpretor->SetTextBlockShape(*Parameters,fading_rectangle);
                }
                else
                {
                    goto wrong_argument;
                }
            }
            else if (word.starts_with("main_block_height"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1080 || value < 0)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetTextBlockHeight(*Parameters,value);
            }
            else if (word.starts_with("main_block_lenght"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1920 || value < 0)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetTextBlockLength(*Parameters,value);
            }
            else if (word.starts_with("main_block_x_coord"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1080 || value < 0)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetTextBlockXPosition(*Parameters,value);
            }
            else if (word.starts_with("main_block_y_coord"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1920 || value < 0)
                {
                    goto wrong_argument;
                }
                m_interpretor->SetTextBlockYPosition(*Parameters,value);
            }
        }
        else if (word.starts_with("opacity"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 100 || value < 0)
            {
                goto wrong_argument;
            }
            m_interpretor->SetTextBlockOpacity(*Parameters,value);
        }
        else if (word.starts_with("font_size"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 100 || value <= 0)
            {
                goto wrong_argument;
            }
            m_interpretor->SetFontSize(*Parameters,value);
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
