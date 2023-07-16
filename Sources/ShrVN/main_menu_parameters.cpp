#include "main_menu_parameters.hpp"

using namespace std;

ostream & operator<<(ostream & os, MainMenuParameters mmp)
{
    return os << "background image " << mmp.m_background_image << endl
              << "logo image " << mmp.m_logo_image << endl
              << "logo pos " << mmp.m_logo_pos << endl
              << "new game pos " << mmp.m_new_game_pos << endl
              << "credit btn pos " << mmp.m_credit_btn_pos << endl
              << "load save pos " << mmp.m_load_save_pos << endl;
}

void InitMenu(ofstream & file)
{
    file << "// relative path (from the image folder) to the image in the background" << '\n'
         << '\n'
         << "background_image = a" <<'\n'
         << '\n'
         << "// relative path (from the image folder) to the image used for the logo of the game" <<'\n'
         << '\n'
         << "logo_image = a" << '\n'
         << '\n'
         << "// x pos of the logo image (bottom left of the image)" << '\n'
         << '\n'
         << "logo_xpos = 500" << '\n'
         << '\n'
         << "// y pos of the logo image (bottom left of the image)" << '\n'
         << '\n'
         << "logo_ypos = 700" << '\n'
         << '\n'
         << "// x pos of the new game button (bottom left of the image)" << '\n'
         << '\n'
         << "ng_btn_xpos = 600" << '\n'
         << '\n'
         << "// y pos of the new game button (bottom left of the image)" << '\n'
         << '\n'
         << "ng_btn_ypos = 800" << '\n'
         << '\n'
         << "// x pos of the credit button (bottom left of the image)" << '\n'
         << '\n'
         << "credit_btn_xpos = 500" << '\n'
         << '\n'
         << "// y pos of the credit button (bottom left of the image)" << '\n'
         << '\n'
         << "credit_btn_ypos = 500" << '\n'
         << '\n'
         << "// x pos of the load save button (bottom left of the image)" << '\n'
         << '\n'
         << "load_save_xpos = 500" << '\n'
         << '\n'
         << "// y pos of the load save button (bottom left of the image)" << '\n'
         << '\n'
         << "load_save_ypos = 500";
}
