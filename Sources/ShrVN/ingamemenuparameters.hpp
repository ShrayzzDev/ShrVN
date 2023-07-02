#ifndef INGAMEMENUPARAMETERS_H
#define INGAMEMENUPARAMETERS_H

#include <fstream>

struct InGameMenuParameters
{

};

void InitInGameMenu(const std::ofstream & file);

InGameMenuParameters ReadInGameMenuParametersFile(const std::ofstream & file);

#endif // INGAMEMENUPARAMETERS_H
