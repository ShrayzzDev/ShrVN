#ifndef MAIN_MENU_PARAMETERS_H
#define MAIN_MENU_PARAMETERS_H

#include <fstream>
#include <string>

#include "point.hpp"

struct MainMenuParameters
{
    std::string m_background_image;
    std::string m_logo_image;
    Point m_logo_pos;
    Point m_new_game_pos;
    Point m_load_save_pos;
    Point m_credit_btn_pos;
};

void InitMenu(const std::ofstream & file);

MainMenuParameters ReadMenuParametersFile(const std::ofstream & file);

#endif // MAIN_MENU_PARAMETERS_H
