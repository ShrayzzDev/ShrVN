#include "in_game_menu_interpretor.hpp"
#include "in_game_menu_parameters.hpp"

void InGameMenuInterpretor::SetBackgroundImage(InGameMenuParameters &igmp, const std::string &bg_img) const
{
    igmp.m_background_image = bg_img;
}

void InGameMenuInterpretor::SetBgImgOpacity(InGameMenuParameters &igmp, unsigned short bg_img_opacity) const
{
    igmp.m_bg_img_opacity = bg_img_opacity;
}

void InGameMenuInterpretor::SetSaveIcon(InGameMenuParameters &igmp, const std::string &save_icon) const
{
    igmp.m_save_icon = save_icon;
}

void InGameMenuInterpretor::SetOptionIcon(InGameMenuParameters &igmp, const std::string &option_icon) const
{
    igmp.m_option_icon = option_icon;
}

void InGameMenuInterpretor::SetTitleMenuIcon(InGameMenuParameters &igmp, const std::string &ttmi) const
{
    igmp.m_title_menu_icon = ttmi;
}

void InGameMenuInterpretor::SetBtnHeight(InGameMenuParameters &igmp, unsigned short btn_height) const
{
    igmp.m_button_height = btn_height;
}

void InGameMenuInterpretor::SetBtnLength(InGameMenuParameters &igmp, unsigned short btn_length) const
{
    igmp.m_button_length = btn_length;
}
