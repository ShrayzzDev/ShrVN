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

void InitSavesMenu(std::ofstream & file);

std::ostream & operator<<(std::ostream & os, SavesMenuParameters & smp);

#endif // SAVES_MENU_PARAMETERS_H
