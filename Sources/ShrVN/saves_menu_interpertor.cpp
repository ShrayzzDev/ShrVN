#include "saves_menu_interpertor.h"

void SavesMenuInterpretor::SetBackgroundImage(SavesMenuParameters &params, std::string & bgimg)
{
    params.m_background_image = bgimg;
}

void SavesMenuInterpretor::SetNbPages(SavesMenuParameters &params, unsigned short nbpages)
{
    params.m_nb_pages = nbpages;
}

void SavesMenuInterpretor::SetNbSavesPerPages(SavesMenuParameters &params, unsigned short nbsaves)
{
    params.m_nb_saves_per_pages = nbsaves;
}

