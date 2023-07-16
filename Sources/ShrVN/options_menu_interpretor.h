#ifndef OPTIONS_MENU_INTERPRETOR_H
#define OPTIONS_MENU_INTERPRETOR_H

#include "IOptionMenuInterpretor.h"

class OptionsMenuInterpretor : public IOptionsMenuInterpretor
{
public:
    void SetBgImage(OptionsMenuParameters &omp, const std::string &bg_img) const override;
    void SetSoundIcon(OptionsMenuParameters &omp, const std::string &sound_icon) const override;
    void SetVideoIcon(OptionsMenuParameters &omp, const std::string &video_icon) const override;
    void SetControlIcon(OptionsMenuParameters &omp, const std::string &contr_icon) const override;
    void SetBtnHeight(OptionsMenuParameters &omp, unsigned short btn_height) const override;
    void SetBtnLength(OptionsMenuParameters &omp, unsigned short btn_length) const override;
};

#endif // OPTIONS_MENU_INTERPRETOR_H
