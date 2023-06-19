#include "characters.hpp"

#include <stdexcept>

using namespace std;

Characters::Characters(const string & name, unsigned short name_red_value, unsigned short name_green_value, unsigned short name_blue_value)
    : m_name{name}
{
    if (name_red_value > 255 || name_blue_value > 255 || name_green_value > 255)
    {
        throw length_error("Error : RBG Value is wrong");
        return;
    }
    m_name_color_red = name_red_value;
    m_name_color_green = name_green_value;
    m_name_color_blue = name_blue_value;
}
