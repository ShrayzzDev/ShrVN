#include "in_game_menu_parameters.hpp"

using namespace std;

ostream & operator<<(ostream & os, InGameMenuParameters igmp)
{
    return os << "Background image : " << igmp.m_background_image << endl
              << "Bg_img_opacity : " << igmp.m_bg_img_opacity << endl
              << "Save icon : " << igmp.m_save_icon << endl
              << "Load icon : " << igmp.m_load_icon << endl
              << "Option icon : " << igmp.m_option_icon << endl
              << "Title Menu icon : " << igmp.m_title_menu_icon << endl
              << "Button Height : " << igmp.m_button_height << endl
              << "Button Length : " << igmp.m_button_length << endl;
}

void InitInGameMenu(ofstream & file)
{
    file << "// Path (relative to the images/ folder) for the image used for the background" << '\n'
         << '\n'
         << "background_img_path = none" <<'\n'
         << '\n'
         << "// Opacity of that said image" <<'\n'
         << '\n'
         << "background_img_opacity = 100"<<'\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the save icon " << '\n'
         << '\n'
         << "save_icon = none" << '\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the load icon " << '\n'
         << '\n'
         << "load_icon = none" << '\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the option icon " << '\n'
         << '\n'
         << "option_icon = none" << '\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the title menu icon " << '\n'
         << '\n'
         << "title_menu_icon = none" << '\n'
         << '\n'
         << "// Height for each button (NOTE : every buttons on this menu have the sames height)" <<'\n'
         << '\n'
         << "btn_height = 50" <<'\n'
         << '\n'
         << "// Length for each button (NOTE : every buttons on this menu have the sames length)" <<'\n'
         << '\n'
         << "btn_length = 50";
}
