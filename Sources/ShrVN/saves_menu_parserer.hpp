#ifndef SAVESMENUPARSERER_HPP
#define SAVESMENUPARSERER_HPP

#include "isave_menu_interpretor.hpp"

class SavesMenuParserer
{
    ISaveMenuInterpretor * m_interpretor;
public:
    SavesMenuParserer(ISaveMenuInterpretor * interpretor);
    SavesMenuParameters * ReadSavesMenuParametersFile(std::ifstream & file);
};

#endif // SAVESMENUPARSERER_HPP
