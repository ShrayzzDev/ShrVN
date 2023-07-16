#ifndef IN_GAME_MENU_PARSERER_H
#define IN_GAME_MENU_PARSERER_H

#include <fstream>

#include "IInGameMenuInterpretor.h"

class InGameMenuParserer
{
    IInGameMenuInterpretor * m_interpretor;
public:
    InGameMenuParserer(IInGameMenuInterpretor * interpretor);
    InGameMenuParameters * ReadInGameMenuParametersFile(std::ifstream & file);
};

#endif // IN_GAME_MENU_PARSERER_H
