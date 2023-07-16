#include "options_menu_interpretor.h"

void OptionsMenuInterpretor::SetBgImage(OptionsMenuParameters &omp, const std::string &bg_img) const
{
    omp.m_background_image = bg_img;
}

void OptionsMenuInterpretor::SetSoundIcon(OptionsMenuParameters &omp, const std::string &sound_icon) const
{
    omp.m_sound_icon = sound_icon;
}

void OptionsMenuInterpretor::SetVideoIcon(OptionsMenuParameters &omp, const std::string &video_icon) const
{
    omp.m_video_icon = video_icon;
}

void OptionsMenuInterpretor::SetControlIcon(OptionsMenuParameters &omp, const std::string &contr_icon) const
{
    omp.m_control_icon = contr_icon;
}

void OptionsMenuInterpretor::SetBtnHeight(OptionsMenuParameters &omp, unsigned short btn_height) const
{
    omp.m_btn_height = btn_height;
}

void OptionsMenuInterpretor::SetBtnLength(OptionsMenuParameters &omp, unsigned short btn_length) const
{
    omp.m_btn_length = btn_length;
}
