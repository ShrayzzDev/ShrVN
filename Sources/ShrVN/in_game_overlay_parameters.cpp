#include "in_game_overlay_parameters.hpp"
#include "parserer_utils.h"

#include <iostream>

using namespace std;

ostream & operator<<(ostream & os, InGameOverlayParameters & Parameters)
{
    switch (Parameters.m_text_mode)
    {
        case(ADV):
            os << "ADV" << endl;
            break;

        case(NVL):
            os << "NVL" << endl;
            break;
    };
    switch (Parameters.m_option_position)
    {
        case(inside_bottom):
            os << "inside_bottom" << endl;
            break;

        case(inside_top):
            os << "inside_top" << endl;
            break;

        case(outside_right):
            os << "outside_right" << endl;
            break;

        case(outside_left):
            os << "outside_left" << endl;
            break;

        case(none):
            os << "none" << endl;
            break;
    };
    switch (Parameters.m_block_shape)
    {
        case(base_rectangle):
            os << "base_rectangle" << endl;
            break;

        case(fading_rectangle):
            os << "fading_rectangle" << endl;
            break;
    };
    os << "block height : " << Parameters.m_text_block_height << endl;
    os << "block lenght : " << Parameters.m_text_block_lenght << endl;
    os << "block opacity : " << Parameters.m_text_block_opacity << endl;
    os << "block position : " << Parameters.m_text_block_position << endl;
    os << "font size : " << Parameters.m_font_size << endl;
    return os;
}

void InitInGameOverlay(ofstream & file)
{
    file << "// NOTE : Games mentionned for examples here aren't made with this engine" << '\n'
         << '\n'
         << "// ADV style : The most used style, found in most visual novels" << '\n'
         << "// Games examples : Clannad, Doki Doki Litterature Club " << '\n'
         << "// NVL style : Text takes all screen" << '\n'
         << "// Games examples : Fate series, Umineko" << '\n'
         << "// It is possible to use both (by changing the style in the main script)" << '\n'
         << "// This defines the style used when creating a new game. By default it's ADV" << '\n'
         << '\n'
         << "text_mode = ADV" << '\n'
         << '\n'
         << "// This parameter defines where the in-game options buttons should show" << '\n'
         << "// inside_bottom : will show inside the text block, at the bottom of it" << '\n'
         << "// outside_right : will show outside the text block, at the right of it" << '\n'
         << "// outside_left : will show outdie the text block, at the left of it" << '\n'
         << "// NOTE : Used only in ADV mode." << '\n'
         << '\n'
         << "in_game_option_position = inside_bottom" << '\n'
         << '\n'
         << "// This parameter defines how the text block shoudl look" << '\n'
         << "// base_rectangle = a rectangle with rounded corners" << '\n'
         << "// fading_rectangle = a rectangle that gradualy fades to the screen borders" << '\n'
         << "// NOTE : Used only in ADV mode." << '\n'
         << '\n'
         << "main_block_shape = base_rectangle" << '\n'
         << '\n'
         << "// Height of the main text block" << '\n'
         << "// NOTE : Used only in ADV mode." << '\n'
         << '\n'
         << "main_block_height = 250" << '\n'
         << '\n'
         << "// Lenght of the main text block" << '\n'
         << "// NOTE : Used only in ADV mode and with base_rectangle main block shape." << '\n'
         << '\n'
         << "main_block_lenght = 750" << '\n'
         << '\n'
         << "// Opacity of the main text block." << '\n'
         << "// 100 = completely opaque" << '\n'
         << "// 0 = completely see through (well 0 should not be that usefull" << '\n'
         << '\n'
         << "opacity = 80" << '\n'
         << '\n'
         << "// coordinates of the main text block (corresponds to the bottom right of the block)" << '\n'
         << "// NOTE : Used only in ADV mode." << '\n'
         << '\n'
         << "main_block_x_coord = 20" << '\n'
         << "main_block_y_coord = 165 (used only in base_rectangle shape)" << '\n'
         << '\n'
         << "// Size of the text" << '\n'
         << '\n'
         << "font_size = 17";
}

InGameOverlayParameters * ReadInGameOverlayParametersFile(ifstream & file)
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
                Parameters->m_text_mode = ADV;
            }
            else if (next_word == "NVL")
            {
                Parameters->m_text_mode = NVL;
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
                Parameters->m_option_position = inside_bottom;
            }
            else if (next_word == "outside_right")
            {
                Parameters->m_option_position = outside_right;
            }
            else if (next_word == "outside_left")
            {
                Parameters->m_option_position = outside_left;
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
                    Parameters->m_block_shape = base_rectangle;
                }
                else if (next_word == "fading_rectangle")
                {
                    Parameters->m_block_shape = fading_rectangle;
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
                Parameters->m_text_block_height = value;
            }
            else if (word.starts_with("main_block_lenght"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1920 || value < 0)
                {
                    goto wrong_argument;
                }
                Parameters->m_text_block_lenght = value;
            }
            else if (word.starts_with("main_block_x_coord"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1080 || value < 0)
                {
                    goto wrong_argument;
                }
                Parameters->m_text_block_position.m_x = value;
            }
            else if (word.starts_with("main_block_y_coord"))
            {
                ReadIntVarAssignation(file,word,value);
                if (value > 1920 || value < 0)
                {
                    goto wrong_argument;
                }
                Parameters->m_text_block_position.m_y = value;
            }
        }
        else if (word.starts_with("opacity"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 100 || value < 0)
            {
                goto wrong_argument;
            }
            Parameters->m_text_block_opacity = value;
        }
        else if (word.starts_with("font_size"))
        {
            ReadIntVarAssignation(file,word,value);
            if (value > 100 || value <= 0)
            {
                goto wrong_argument;
            }
            Parameters->m_font_size = value;
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
