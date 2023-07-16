#ifndef IOPTIONMENUINTERPRETOR_H
#define IOPTIONMENUINTERPRETOR_H

#include <string>

#include "options_menu_parameters.hpp"

class IOptionsMenuInterpretor
{
public:
    virtual void SetBgImage(OptionsMenuParameters & omp, const std::string & bg_img) const = 0;
    virtual void SetSoundIcon(OptionsMenuParameters & omp, const std::string & sound_icon) const = 0;
    virtual void SetVideoIcon(OptionsMenuParameters & omp, const std::string & video_icon) const = 0;
    virtual void SetControlIcon(OptionsMenuParameters & omp, const std::string & contr_icon) const = 0;
    virtual void SetBtnHeight(OptionsMenuParameters & omp, unsigned short btn_height) const = 0;
    virtual void SetBtnLength(OptionsMenuParameters & omp, unsigned short btn_length) const = 0;
};

#endif // IOPTIONMENUINTERPRETOR_H
