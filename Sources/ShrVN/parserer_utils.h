#ifndef PARSERER_UTILS_H
#define PARSERER_UTILS_H

#include <string>
#include <fstream>

void ReadStringVarAssignation(std::ifstream & file, const std::string & word, std::string & result);

void ReadIntVarAssignation(std::ifstream & file, const std::string & word, int & result);

bool CheckEmptyLine(std::ifstream & file);

bool CheckComment(std::ifstream & file, const std::string & word);

#endif // PARSERER_UTILS_H
