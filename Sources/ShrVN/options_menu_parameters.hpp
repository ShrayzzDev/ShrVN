#ifndef OPTIONS_MENU_PARAMETERS_H
#define OPTIONS_MENU_PARAMETERS_H

#include <fstream>
#include <string>

struct OptionsMenuParameters
{
    std::string m_background_image;
};

void InitOptionsMenu(const std::ofstream & file);

OptionsMenuParameters ReadOptionsMenuParametersFile(const std::ofstream & file);

#endif // OPTIONS_MENU_PARAMETERS_H
