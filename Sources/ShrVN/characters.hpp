#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <string>
#include <map>

class Characters
{
    std::string m_name;
    std::map<std::string,std::string> m_char_pictures;
    std::string m_image_folder_name;
    unsigned short m_name_color_red;
    unsigned short m_name_color_green;
    unsigned short m_name_color_blue;
public:
    Characters(const std::string & name, unsigned short name_red_value = 255, unsigned short name_green_value = 255, unsigned short name_blue_value = 255);
    int GetRedValue() const;
    int GetBlueValue() const;
    int GetGreenValue() const;
    const std::string & GetName() const;
    const std::string & GetImage(const std::string & image_name);
};

#endif // CHARACTERS_HPP
