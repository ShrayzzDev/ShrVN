#ifndef IN_GAME_MENU_PARAMETERS_H
#define IN_GAME_MENU_PARAMETERS_H

#include <fstream>

struct InGameMenuParameters
{

};

void InitInGameMenu(const std::ofstream & file);

InGameMenuParameters ReadInGameMenuParametersFile(const std::ofstream & file);

#endif // IN_GAME_MENU_PARAMETERS_H
