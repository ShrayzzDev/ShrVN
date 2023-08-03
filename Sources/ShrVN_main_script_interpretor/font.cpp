#include <list>
#include <string>
#include <cstring>
#include <iostream>
#include <filesystem>

#include "font.h"

TTF_Font * CreateFont(const std::string & font_type, unsigned short font_size)
{
    std::list<std::string> folders_to_check;
    if (std::filesystem::exists("fonts/"))
    {
        folders_to_check.push_back("fonts/");
    }
#ifdef _WIN64
    folders_to_check.push_back("C:/Windows/Fonts");
    char * user_fonts = getenv("appdata");
    std::strcat(user_fonts,"/../Local/Microsoft/Windows/Fonts");
    folders_to_check.push_back(user_fonts);
#elif __linux__
    folders_to_check.push_back("/usr/share/fonts");
    folders_to_check.push_back("/usr/local/share/fonts");
    if (std::filesystem::exists("~/.local/share/fonts"))
    {
        folders_to_check.push_back("~/.local/share/fonts");
    }
#endif
    for (auto const& font_folder : folders_to_check)
    {
        for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{font_folder})
        {
            const std::filesystem::path & current_font = dir_entry.path();
            if (current_font.filename().stem().generic_string() == font_type)
            {
                if (!current_font.filename().generic_string().ends_with(".ttf"))
                {
                    throw std::invalid_argument("ERROR : Couldn't open the defined font because of wrong format (should be .ttf");
                }
                TTF_Font * font;
                font = TTF_OpenFont(current_font.generic_string().c_str(),font_size);
                if (font == NULL)
                {
                    std::cout << SDL_GetError() << std::endl;
                }
                return font;
            }
        }
    }
    return NULL;
}
