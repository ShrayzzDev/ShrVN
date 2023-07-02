#ifndef OPTIONSMENUPARAMETERS_H
#define OPTIONSMENUPARAMETERS_H

#include <fstream>

class OptionsMenuParameters
{

};

void InitOptionsMenu(const std::ofstream & file);

OptionsMenuParameters ReadOptionsMenuParametersFile(const std::ofstream & file);

#endif // OPTIONSMENUPARAMETERS_H
