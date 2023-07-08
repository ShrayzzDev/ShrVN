#ifndef MAIN_MENU_PARAMETERS_H
#define MAIN_MENU_PARAMETERS_H

#include <fstream>
#include <string>

#include "point.hpp"

struct MainMenuParameters
{
    std::string m_background_image;
    Point m_new_game_position;
};

void InitMenu(const std::ofstream & file);

MainMenuParameters ReadMenuParametersFile(const std::ofstream & file);

#endif // MAIN_MENU_PARAMETERS_H
