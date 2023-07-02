#ifndef SAVESMENUPARAMETERS_H
#define SAVESMENUPARAMETERS_H

#include <fstream>

class SavesMenuParameters
{

};

void InitSavesMenu(const std::ofstream & file);

SavesMenuParameters ReadSavesMenuParametersFile(const std::ofstream & file);

#endif // SAVESMENUPARAMETERS_H
