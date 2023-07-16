#ifndef OPTIONMENUPARSERER_HPP
#define OPTIONMENUPARSERER_HPP

#include "IOptionMenuInterpretor.h"

class OptionsMenuParserer
{
    IOptionsMenuInterpretor * m_interpretor;
public:
    OptionsMenuParserer(IOptionsMenuInterpretor * interpretor);
    OptionsMenuParameters * ReadOptionMenuParametersFile(std::ifstream & file);
};

#endif // OPTIONMENUPARSERER_HPP
