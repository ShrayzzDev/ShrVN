#include <filesystem>
#include <fstream>
#include <iostream>
#include <string.h>

#include "characters.hpp"
#include "characterparserer.h"

using namespace std;

CharacterParserer::CharacterParserer(ICharacterInterpreter *interpreter)
    :m_interpreter{interpreter}
{

}

map<string,Characters> * CharacterParserer::ParseCharacterFile()
{

    string file_name = "Characters.shrvn";
    if ( !filesystem::exists(file_name))
    {
        throw filesystem::filesystem_error("ERROR : the directory " + file_name + " couldn't be found. Can't inialise the characters, ending program.",error_code());
    }
    map<string, Characters> *Character_map = new map<string, Characters>();
    ifstream read_file(file_name);
    string instance_name, character_name, first_word, temp_int_value, temp;
    unsigned short red_value, green_value, blue_value;
    unsigned long long nb_line = 1;
    while (!read_file.eof())
    {
        if ((char)read_file.peek() == '\n')
        {
            getline(read_file, temp, '\n');
            continue;
        }
        getline(read_file, first_word, ' ');
        if (first_word == "Character")
        {
            getline(read_file, instance_name, '(');
            if (Character_map->find(instance_name) != Character_map->end())
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : There is already a chracter with this instance name.");
            }
            char temp_dbquotes;
            read_file.get(temp_dbquotes);
            if (temp_dbquotes != '"')
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : characters name must be between quotes");
            }
            getline(read_file, character_name, '"');
            char closing_parenthesis;
            read_file.get(closing_parenthesis);
            if (closing_parenthesis == ')')
            {
                // (*Character_map).emplace(instance_name,Characters(character_name));
                m_interpreter->AddChar(*Character_map,instance_name,character_name);
                getline(read_file, temp, '\n');
                ++nb_line;
                continue;
            }
            if (closing_parenthesis != ',')
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid enclosure of definition, need a ')' (or a ',' if you want to specify rgb values)");
            }
            red_value = ReadShortValue(read_file,',');
            green_value = ReadShortValue(read_file,',');
            blue_value = ReadShortValue(read_file,')');
            m_interpreter->AddChar(*Character_map,instance_name,character_name,red_value,green_value,blue_value);
            getline(read_file, temp, '\n');
        }
        else if (first_word == "From")
        {
            string next_keyword, image_path;
            getline(read_file, character_name, ' ');
            if (! Character_map->contains(character_name))
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : character " + character_name + " couldn't be found. Maybe a typo ?");
            }
            getline(read_file, next_keyword, ' ');
            if (next_keyword == "Add")
            {
                getline(read_file, image_path, ' ');
                getline(read_file, next_keyword, ' ');
                if (next_keyword != "As")
                {
                    goto unknown_keyword;
                }
                getline(read_file, instance_name, '\n');
                m_interpreter->AddImage(*Character_map,character_name,instance_name,image_path);
            }
            else if (next_keyword == "Show")
            {
                throw invalid_argument("ERROR : line " + to_string(nb_line) + " : can't show an image from the character file.");
            }
            else
            {
                goto unknown_keyword;
            }
            ++nb_line;
            continue;
        }
        else
        {
            goto unknown_keyword;
        }
        ++nb_line;
    }
    return Character_map;
    unknown_keyword:
        throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + first_word + " ' in this context");
}


unsigned short ReadShortValue(std::ifstream &file, char end_of_value)
{
    string temp_int_value;
    getline(file, temp_int_value, end_of_value);
    return stoi(temp_int_value);
}
