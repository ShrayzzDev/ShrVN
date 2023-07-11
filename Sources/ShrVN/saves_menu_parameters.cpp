#include "saves_menu_parameters.hpp"

using namespace std;

std::ostream & operator<<(std::ostream & os, SavesMenuParameters & smp)
{
    return os << smp.m_background_image << endl
              << smp.m_nb_pages << endl
              << smp.m_nb_saves_per_pages << endl;
}

void InitSavesMenu(ofstream & file)
{
    file << "// path to the image used for the background of the save page." << '\n'
         << '\n'
         << "background_image = none" << '\n'
         << '\n'
         << "// number of pages for saves (max = 10)" << '\n'
         << '\n'
         << "nb_pages = 5" << '\n'
         << '\n'
         << "// number of saves by pages (max = 10)" << '\n'
         << '\n'
         << "nb_saves = 10";
}
