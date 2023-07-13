#include "main_menu_interpretor.hpp"

using namespace std;

void MainMenuInterpretor::SetBackgroundImage(MainMenuParameters & mmp, string bg_img_path) const
{
    mmp.m_background_image = bg_img_path;
}

void MainMenuInterpretor::SetLogoImg(MainMenuParameters & mmp, std::string logo_img_path) const
{
    mmp.m_logo_image = logo_img_path;
}

void MainMenuInterpretor::SetLogoXPos(MainMenuParameters & mmp, unsigned short xpos) const
{
    mmp.m_logo_pos.m_x = xpos;
}

void MainMenuInterpretor::SetLogoYPos(MainMenuParameters & mmp, unsigned short ypos) const
{
    mmp.m_logo_pos.m_y = ypos;
}

void MainMenuInterpretor::SetNewGameXPos(MainMenuParameters & mmp, unsigned short xpos) const
{
    mmp.m_new_game_pos.m_x = xpos;
}

void MainMenuInterpretor::SetNewGameYPos(MainMenuParameters & mmp, unsigned short ypos) const
{
    mmp.m_new_game_pos.m_y = ypos;
}

void MainMenuInterpretor::SetLoadSaveXPos(MainMenuParameters & mmp, unsigned short xpos) const
{
    mmp.m_load_save_pos.m_x = xpos;
}

void MainMenuInterpretor::SetLoadSaveYPos(MainMenuParameters & mmp, unsigned short ypos) const
{
    mmp.m_load_save_pos.m_y = ypos;
}

void MainMenuInterpretor::SetCreditXPos(MainMenuParameters & mmp, unsigned short xpos) const
{
    mmp.m_credit_btn_pos.m_x = xpos;
}

void MainMenuInterpretor::SetCreditYPos(MainMenuParameters & mmp, unsigned short ypos) const
{
    mmp.m_credit_btn_pos.m_y = ypos;
}
