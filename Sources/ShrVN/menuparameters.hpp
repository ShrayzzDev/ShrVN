#ifndef MENUPARAMETERS_HPP
#define MENUPARAMETERS_HPP

#include <fstream>

struct MenuParameters
{

};

void InitMenu(const std::ofstream & file);

MenuParameters ReadMenuParametersFile(const std::ofstream & file);

#endif // MENUPARAMETERS_HPP
