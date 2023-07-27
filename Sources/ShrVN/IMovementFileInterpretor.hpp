#ifndef IMOVEMENTFILEINTERPRETOR_H
#define IMOVEMENTFILEINTERPRETOR_H

#include <string>
#include <map>

#include "movement.h"

class IMovementFileInterpretor
{
public:
    virtual void CreateMovement(std::map<std::string,Movement> & mp_mvt, std::list<Point> & mvt, const std::string & mvt_name) const = 0;
};

#endif // IMOVEMENTFILEINTERPRETOR_H
