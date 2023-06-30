#ifndef CHARACTERS_HPP
#define CHARACTERS_HPP

#include <string>
#include <map>

class Characters
{
    inline static std::string default_images_keywords[2] = {"default","not_found"};
    inline static std::string image_not_found = "nothing";
    std::string m_name;
    std::map<std::string,std::string> m_char_pictures;
    std::string m_image_folder_name;
    unsigned short m_name_color_red;
    unsigned short m_name_color_green;
    unsigned short m_name_color_blue;
public:
    Characters(const std::string & name, unsigned short name_red_value = 255, unsigned short name_green_value = 255, unsigned short name_blue_value = 255);
    unsigned short GetRedValue() const;
    unsigned short GetGreenValue() const;
    unsigned short GetBlueValue() const;
    void SetRedValue(unsigned short red_value);
    void SetGreenValue(unsigned short green_value);
    void SetBlueValue(unsigned short blue_value);
    const std::string & GetName() const;
    const std::string & GetImage(const std::string & image_name) const;
    bool AddImage(const std::string & image_name, const std::string & image_path = "");
    friend const std::string & DefaultImage(const Characters & Character);
};

const std::string & DefaultImage(const Characters & Character);

#endif // CHARACTERS_HPP
