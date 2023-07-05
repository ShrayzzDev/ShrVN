#include <filesystem>
#include <fstream>
#include <iostream>

#include "characters.hpp"
#include "parserer.h"

using namespace std;

map<string,Characters> * ParseCharacterFile()
{

    string file_name = "Characters.shrvn";
    if ( !filesystem::exists(file_name))
    {
        throw filesystem::filesystem_error("ERROR : the directory " + file_name + " couldn't be found. Can't inialise the characters, ending program.",error_code());
    }
    map<string, Characters> *Character_map = new map<string, Characters>();
    ifstream read_file(file_name);
    string instance_name, character_name, first_word, temp_int_value, temp;
    unsigned short red_value = 255, green_value = 255, blue_value = 255;
    unsigned long long nb_line = 1;
    while (!read_file.eof())
    {
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
                (*Character_map).emplace(instance_name,Characters(character_name));
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
            (*Character_map).emplace(instance_name, Characters(character_name,red_value,green_value,blue_value));
            getline(read_file, temp, '\n');
        }
        else if (first_word == "From")
        {
            ++nb_line;
            continue;
        }
        else
        {
            throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + first_word + " '");
        }
        ++nb_line;
    }
    return Character_map;
}


unsigned short ReadShortValue(std::ifstream &file, char end_of_value)
{
    string temp_int_value;
    getline(file, temp_int_value, end_of_value);
    return stoi(temp_int_value);
}
