#ifndef PARSERER_H
#define PARSERER_H

#include <map>
#include <string>
#include <fstream>

class Characters;

std::map<std::string,Characters> * ParseCharacterFile();

unsigned short ReadShortValue(std::ifstream & file, char end_of_value);

#endif // PARSERER_H
