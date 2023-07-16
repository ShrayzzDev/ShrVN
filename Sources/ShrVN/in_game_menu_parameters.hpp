#ifndef IN_GAME_MENU_PARAMETERS_H
#define IN_GAME_MENU_PARAMETERS_H

#include <fstream>
#include <string>

struct InGameMenuParameters
{
    std::string m_background_image;
    unsigned short m_bg_img_opacity;
    std::string m_save_icon;
    std::string m_load_icon;
    std::string m_option_icon;
    std::string m_title_menu_icon;
    unsigned short m_button_height;
    unsigned short m_button_length;
};

std::ostream & operator<<(std::ostream & os, InGameMenuParameters igmp);

void InitInGameMenu(std::ofstream & file);

#endif // IN_GAME_MENU_PARAMETERS_H
