#include "movement.h"

std::ostream & operator<<(std::ostream & os, Movement & mvt)
{
    return os << mvt.control_points
              << "During :" << mvt.duration << std::endl;
}

std::ostream & operator<<(std::ostream & os, std::map<std::string,Movement> & map_mvt)
{
    for(auto mvt : map_mvt)
    {
        os << "Mvt name: " << mvt.first << std::endl
           << mvt.second << std::endl;
    }
}
