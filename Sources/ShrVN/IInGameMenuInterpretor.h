#ifndef IINGAMEMENUINTERPRETOR_H
#define IINGAMEMENUINTERPRETOR_H

#include "in_game_menu_parameters.hpp"

class IInGameMenuInterpretor
{
public:
    virtual void SetBackgroundImage(InGameMenuParameters & igmp, const std::string & bg_img) const = 0;
    virtual void SetBgImgOpacity(InGameMenuParameters & igmp, unsigned short bg_img_opacity) const = 0;
    virtual void SetSaveIcon(InGameMenuParameters & igmp, const std::string & save_icon) const = 0;
    virtual void SetLoadIcon(InGameMenuParameters & igmp, const std::string & load_icon) const = 0;
    virtual void SetOptionIcon(InGameMenuParameters & igmp, const std::string & option_icon) const = 0;
    virtual void SetTitleMenuIcon(InGameMenuParameters & igmp, const std::string & ttmi) const = 0;
    virtual void SetBtnHeight(InGameMenuParameters & igmp, unsigned short btn_height) const = 0;
    virtual void SetBtnLength(InGameMenuParameters & igmp, unsigned short btn_length) const = 0;
};

#endif // IINGAMEMENUINTERPRETOR_H
