#ifndef MAINMENUPARSERER_HPP
#define MAINMENUPARSERER_HPP

#include "IMainMenuInterpretor.h"
#include "main_menu_parameters.hpp"

class MainMenuParserer
{
    IMainMenuInterpretor * m_interpretor;
public:
    MainMenuParserer(IMainMenuInterpretor * interpretor);
    MainMenuParameters * ReadMainMenuParametersFile(std::ifstream & file);
};

#endif // MAINMENUPARSERER_HPP
