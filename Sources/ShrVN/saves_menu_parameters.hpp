#ifndef SAVES_MENU_PARAMETERS_H
#define SAVES_MENU_PARAMETERS_H

#include <fstream>
#include <string>

struct SavesMenuParameters
{
    std::string m_background_image;
    unsigned short m_nb_pages;
    unsigned short m_nb_saves_per_pages;
};

void InitSavesMenu(const std::ofstream & file);

SavesMenuParameters ReadSavesMenuParametersFile(const std::ofstream & file);

#endif // SAVES_MENU_PARAMETERS_H
