#ifndef MOVEMENT_FILE_PARSERER_H
#define MOVEMENT_FILE_PARSERER_H

#include "IMovementFileInterpretor.hpp"

class MovementFileParserer
{
    IMovementFileInterpretor * m_interpretor;
public:
    MovementFileParserer(IMovementFileInterpretor * interpretor);
    std::map<std::string,Movement> * FileParserer(std::ifstream & file);
};

#endif // MOVEMENT_FILE_PARSERER_H
