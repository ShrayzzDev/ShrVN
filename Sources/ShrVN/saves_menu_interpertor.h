#ifndef SAVES_MENU_INTERPERTOR_H
#define SAVES_MENU_INTERPERTOR_H

#include "isave_menu_interpretor.hpp"

class SavesMenuInterpretor : public ISaveMenuInterpretor
{
public:
    void SetBackgroundImage(SavesMenuParameters &params, std::string &bgimg) override;
    void SetNbPages(SavesMenuParameters &params, unsigned short nbpages) override;
    void SetNbSavesPerPages(SavesMenuParameters &params, unsigned short nbsaves) override;
};

#endif // SAVES_MENU_INTERPERTOR_H
