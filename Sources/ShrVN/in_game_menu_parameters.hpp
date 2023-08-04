#ifndef IN_GAME_MENU_PARAMETERS_H
#define IN_GAME_MENU_PARAMETERS_H

#include <fstream>
#include <string>

struct InGameMenuParameters
{
    std::string m_background_image;
    unsigned short m_bg_img_opacity;
    std::string m_save_icon = "save.png";
    std::string m_option_icon = "settings.png";
    std::string m_title_menu_icon = "tmi.png";
    unsigned short m_button_height = 50;
    unsigned short m_button_length = 50;
};

std::ostream & operator<<(std::ostream & os, InGameMenuParameters igmp);

void InitInGameMenu(std::ofstream & file);

#endif // IN_GAME_MENU_PARAMETERS_H
