#ifndef MOVEMENTINTERPRETOR_H
#define MOVEMENTINTERPRETOR_H

#include "IMovementFileInterpretor.hpp"

class MovementInterpretor : public IMovementFileInterpretor
{
public:
    void CreateMovement(std::map<std::string, Movement> &mp_mvt, std::list<Point> &mvt, const std::string &mvt_name) const override;
};

#endif // MOVEMENTINTERPRETOR_H
