#ifndef OPTIONS_MENU_PARAMETERS_H
#define OPTIONS_MENU_PARAMETERS_H

#include <fstream>
#include <string>

struct OptionsMenuParameters
{
    std::string m_background_image;
    std::string m_sound_icon;
    std::string m_video_icon;
    std::string m_control_icon;
    unsigned short m_btn_height;
    unsigned short m_btn_length;
};

std::ostream & operator<<(std::ostream & os, OptionsMenuParameters & omp);

void InitOptionsMenu(std::ofstream & file);

#endif // OPTIONS_MENU_PARAMETERS_H
