#ifndef IMAINMENUINTERPRETOR_H
#define IMAINMENUINTERPRETOR_H

#include <string>

#include "point.hpp"
#include "main_menu_parameters.hpp"

class IMainMenuInterpretor
{
public:
    virtual void SetBackgroundImage(MainMenuParameters & mmp, std::string bg_img_path) const = 0;
    virtual void SetLogoImg(MainMenuParameters & mmp, std::string logo_img_path) const = 0;
    virtual void SetLogoXPos(MainMenuParameters & mmp, unsigned short xpos) const = 0;
    virtual void SetLogoYPos(MainMenuParameters & mmp, unsigned short ypos) const = 0;
    virtual void SetNewGameXPos(MainMenuParameters & mmp, unsigned short xpos) const = 0;
    virtual void SetNewGameYPos(MainMenuParameters & mmp, unsigned short ypos) const = 0;
    virtual void SetLoadSaveXPos(MainMenuParameters & mmp, unsigned short xpos) const = 0;
    virtual void SetLoadSaveYPos(MainMenuParameters & mmp, unsigned short ypos) const = 0;
    virtual void SetCreditXPos(MainMenuParameters & mmp, unsigned short xpos) const = 0;
    virtual void SetCreditYPos(MainMenuParameters & mmp, unsigned short ypos) const = 0;
};

#endif // IMAINMENUINTERPRETOR_H
