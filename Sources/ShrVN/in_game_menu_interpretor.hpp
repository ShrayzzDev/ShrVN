#ifndef IN_GAME_MENU_INTERPRETOR_H
#define IN_GAME_MENU_INTERPRETOR_H

#include "IInGameMenuInterpretor.h"

class InGameMenuInterpretor : public IInGameMenuInterpretor
{
public:
    void SetBackgroundImage(InGameMenuParameters &igmp, const std::string &bg_img) const override;
    void SetBgImgOpacity(InGameMenuParameters &igmp, unsigned short bg_img_opacity) const override;
    void SetSaveIcon(InGameMenuParameters &igmp, const std::string &save_icon) const override;
    void SetOptionIcon(InGameMenuParameters &igmp, const std::string &option_icon) const override;
    void SetTitleMenuIcon(InGameMenuParameters &igmp, const std::string &ttmi) const override;
    void SetBtnHeight(InGameMenuParameters &igmp, unsigned short btn_height) const override;
    void SetBtnLength(InGameMenuParameters &igmp, unsigned short btn_length) const override;
};

#endif // IN_GAME_MENU_INTERPRETOR_H
