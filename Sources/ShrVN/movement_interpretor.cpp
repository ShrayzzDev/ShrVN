#include "movement_interpretor.h"

void MovementInterpretor::CreateMovement(std::map<std::string, Movement> &mp_mvt, std::vector<Point> &mvt, const std::string &mvt_name) const
{
    std::pair<std::string,std::vector<Point>> nv_mvt = {mvt_name,mvt};
    mp_mvt.emplace(nv_mvt);
}
