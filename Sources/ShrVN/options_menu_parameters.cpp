#include <iostream>>

#include "options_menu_parameters.hpp"

using namespace std;

std::ostream & operator<<(std::ostream & os, OptionsMenuParameters & omp)
{
    return os << "Background image : " << omp.m_background_image << endl
              << "Sound icon : " << omp.m_sound_icon << endl
              << "Control icon : " << omp.m_control_icon << endl
              << "Video icon : " << omp.m_video_icon << endl
              << "Button Height : " << omp.m_btn_height << endl
              << "Button Length : " << omp.m_btn_length << endl;
}

void InitOptionsMenu(std::ofstream & file)
{
    file << "// Path (relative to the images/ folder) for the image used for the background" << '\n'
         << '\n'
         << "background_img_path = none" <<'\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the sound icon " << '\n'
         << '\n'
         << "sound_icon = none" << '\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the control icon " << '\n'
         << '\n'
         << "control_icon = none" << '\n'
         << '\n'
         << "// Path (relative to the images/ folder) for the image used as the video icon " << '\n'
         << '\n'
         << "video_icon = none" << '\n'
         << '\n'
         << "// Height for each button (NOTE : every buttons on this menu have the sames height)" <<'\n'
         << '\n'
         << "btn_height = 50" <<'\n'
         << '\n'
         << "// Length for each button (NOTE : every buttons on this menu have the sames length)" <<'\n'
         << '\n'
         << "btn_length = 50";
}
