#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <map>
#include <string>

#include "point.hpp"

struct Movement
{
    std::vector<Point> control_points;
    long long duration;
};

std::ostream & operator<<(std::ostream & os, Movement & mvt);

std::ostream & operator<<(std::ostream & os, std::map<std::string,Movement> & map_mvt);

#endif // MOVEMENT_H
