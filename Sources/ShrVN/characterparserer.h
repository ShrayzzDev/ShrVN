#ifndef CHARACTERPARSERER_H
#define CHARACTERPARSERER_H

#include <map>
#include <string>
#include <fstream>

#include "icharacterinterpreter.hpp"

class Characters;

class CharacterParserer
{
    ICharacterInterpreter *m_interpreter;
public:
    CharacterParserer(ICharacterInterpreter *interpreter);
    std::map<std::string,Characters> * ParseCharacterFile();
};

unsigned short ReadShortValue(std::ifstream & file, char end_of_value);

#endif // CHARACTERPARSERER_H
