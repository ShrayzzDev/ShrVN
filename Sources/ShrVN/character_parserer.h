#ifndef CHARACTER_PARSERER_H
#define CHARACTER_PARSERER_H

#include <map>
#include <string>
#include <fstream>

#include "ICharacter_Interpreter.hpp"

class Characters;

class CharacterParserer
{
    ICharacterInterpreter *m_interpreter;
public:
    CharacterParserer(ICharacterInterpreter *interpreter);
    std::map<std::string,Characters> * ParseCharacterFile();
};

unsigned short ReadShortValue(std::ifstream & file, char end_of_value);

#endif // CHARACTER_PARSERER_H
