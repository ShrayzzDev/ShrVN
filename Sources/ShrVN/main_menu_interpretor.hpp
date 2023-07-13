#ifndef MAINMENUINTERPRETOR_HPP
#define MAINMENUINTERPRETOR_HPP

#include "IMainMenuInterpretor.h"

class MainMenuInterpretor : public IMainMenuInterpretor
{
public:
    void SetBackgroundImage(MainMenuParameters & mmp, std::string bg_img_path) const override;
    void SetLogoImg(MainMenuParameters & mmp, std::string logo_img_path) const override;
    void SetLogoXPos(MainMenuParameters & mmp, unsigned short xpos) const override;
    void SetLogoYPos(MainMenuParameters & mmp, unsigned short ypos) const override;
    void SetNewGameXPos(MainMenuParameters &  mmp, unsigned short xpos) const override;
    void SetNewGameYPos(MainMenuParameters & mmp, unsigned short ypos) const override;
    void SetLoadSaveXPos(MainMenuParameters & mmp, unsigned short xpos) const override;
    void SetLoadSaveYPos(MainMenuParameters & mmp, unsigned short ypos) const override;
    void SetCreditXPos(MainMenuParameters & mmp, unsigned short xpos) const override;
    void SetCreditYPos(MainMenuParameters & mmp, unsigned short ypos) const override;
};

#endif // MAINMENUINTERPRETOR_HPP
