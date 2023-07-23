#include "characters.hpp"

#include <filesystem>
#include <iostream>
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
    filesystem::path full_image_path = filesystem::current_path().generic_string() + "/images/" + m_name;
    if (!filesystem::exists(full_image_path))
    {
        filesystem::create_directory(full_image_path);
    }
    m_image_folder_name = m_name + "/";
}

unsigned short Characters::GetRedValue() const
{
    return m_name_color_red;
}

unsigned short Characters::GetGreenValue() const
{
    return m_name_color_green;
}

unsigned short Characters::GetBlueValue() const
{
    return m_name_color_blue;
}

void Characters::SetRedValue(unsigned short red_value)
{
    if (red_value > 255)
    {
        throw length_error("ERROR : You tried to set a value supperior to 255 for the red value");
        return;
    }
    m_name_color_red = red_value;
}

void Characters::SetGreenValue(unsigned short green_value)
{
    if (green_value > 255)
    {
        throw length_error("ERROR : You tried to set a value supperior to 255 for the green value");
        return;
    }
    m_name_color_green = green_value;
}

void Characters::SetBlueValue(unsigned short blue_value)
{
    if (blue_value > 255)
    {
        throw length_error("ERROR : You tried to set a value supperior to 255 for the blue value");
        return;
    }
    m_name_color_blue = blue_value;
}

const string & Characters::GetName() const
{
    return m_name;
}

const string & Characters::GetImage(const string & image_name) const
{
    if (image_name == "not_found" || image_name == "default")
    {
        cerr << "WARNING : Consider renaming this sprite another way, as the '" << image_name
             << "' 's main purpose is to show an image if this software doesn't find an image." << endl;
        return m_char_pictures.at(image_name);
    }
    if (m_char_pictures.find(image_name) == m_char_pictures.end())
    {
        cerr << "ERROR : The image " << image_name
             << " from character " + m_name
             << " couldn't be found." << endl;
        return DefaultImage(*this);
    }
    filesystem::path full_image_path = filesystem::current_path().generic_string() + "/images/" + m_char_pictures.at(image_name);
    if (! filesystem::exists(full_image_path))
    {
        cerr << "ERROR : Didn't find the image " << image_name
             << " in the folder " + filesystem::current_path().generic_string() << "/images/" << m_image_folder_name << " ."
             << " Did you delete it while the program was running ?" << endl;
        return DefaultImage(*this);
    }
    return m_char_pictures.at(image_name);
}

bool Characters::AddImage(const string & image_instance_name, const string & image_name, const string & image_path)
{
    if (image_instance_name.size() == 1)
    {
        cerr << "ERROR : The name of the instance is too short/empty. Name it another way. (short names usualy are a bad idea)" << endl;
        return false;
    }
    if (((m_char_pictures.find(image_instance_name) != m_char_pictures.end())))
    {
        cerr << "ERROR : The image " << image_instance_name << " already exists for the character " << m_name << endl;
        return false;
    }
    if ( ! image_name.ends_with(".png") && ! image_name.ends_with(".jpg") && ! image_name.ends_with(".jpeg"))
    {
        cerr << "ERROR : The image " << image_name << " has a wrong format. Needs to be .png, .jpg, .jpeg" << endl;
        return false;
    }
    filesystem::path full_image_path = filesystem::path(filesystem::current_path().generic_string() + "/images/" + m_image_folder_name + image_path + image_name);
    if (! filesystem::exists(full_image_path))
    {
        cerr << "ERROR : The image " << image_name << " couldn't be found in the " + full_image_path.generic_string() << " path" << endl;
        return false;
    }
    m_char_pictures.emplace(image_instance_name,m_image_folder_name + image_path + image_name);
    return true;
}

const string & DefaultImage(const Characters & Character)
{
    for (const string & base : Character.default_images_keywords)
    {
        if (Character.m_char_pictures.find(base) != Character.m_char_pictures.end())
        {
            cerr << "Using the " << base << " sprite instead" << endl;
            return Character.m_char_pictures.at(base);
        }
    }
    cerr << "WARNING : Wasn't able to find the 'not_found' or 'default' image \n Can't show an image, consider defining a 'not_found' 'default' image for that character." << endl;
    return Character.image_not_found;
}
