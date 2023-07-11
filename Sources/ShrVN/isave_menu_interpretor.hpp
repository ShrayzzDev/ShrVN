#ifndef ISAVEMENUINTERPRETOR_HPP
#define ISAVEMENUINTERPRETOR_HPP

#include <string>

#include "saves_menu_parameters.hpp"

class ISaveMenuInterpretor
{  
public:
    virtual void SetBackgroundImage(SavesMenuParameters & params, std::string & bgimg) = 0;
    virtual void SetNbPages(SavesMenuParameters & params, unsigned short nbpages) = 0;
    virtual void SetNbSavesPerPages(SavesMenuParameters & params, unsigned short nbsaves) = 0;
};

#endif // ISAVEMENUINTERPRETOR_HPP
