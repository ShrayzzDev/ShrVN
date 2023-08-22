#include <iostream>
#include "save.h"

std::ostream & operator<<(std::ostream & os, Save & save)
{
    os << "---------------------" << '\n'
       << "Script line: "<< save.m_user_data.script_line <<'\n'
       << "nb dial: "<< save.m_user_data.nb_dial <<'\n';
    for (auto & dial : save.m_buffer.m_previous_dialogue)
    {
        os << dial.first << " : " << dial.second << '\n';
    }
    for (auto & sprt : save.m_buffer.m_on_screen)
    {
        os << sprt.first << sprt.second << '\n';
    }
    return os;
}

Save::Save()
{

}

void Save::ReadBufferFile(std::ifstream &file)
{
    int nb_sprite,i, x_coord, y_coord;
    std::string value, sprite_path, x, y;
    std::getline(file,value,'\n');
    nb_sprite = std::stoi(value);
    for (i = 0; i < nb_sprite; ++i)
    {
        std::getline(file,sprite_path,' ');
        std::getline(file,x,' ');
        x_coord = std::stoi(x);
        std::getline(file,y,'\n');
        y_coord = std::stoi(y);
        m_buffer.m_on_screen.emplace(std::pair<std::string,Point>(sprite_path,{x_coord,y_coord}));
    }
    std::string char_name, dial;
    int nb_dial;
    std::getline(file,value,'\n');
    nb_dial = std::stoi(value);
    for (i = 0; i < nb_dial; ++i)
    {
        std::getline(file,char_name,'\n');
        std::getline(file,dial,'\n');
        m_buffer.m_previous_dialogue.push_front(std::pair<std::string,std::string>(char_name,dial));
    }
    std::getline(file,value,'\n');
    m_buffer.nb_current_dial = stoi(value);
    std::getline(file,value,'\n');
    switch(std::stoi(value)) {
    case 0:
        m_buffer.tm = ADV;
        break;
    case 1:
        m_buffer.tm = NVL;
        break;
    default:
        throw std::invalid_argument("ERROR : Wrong current_screen in the buffer file");
    }
    std::string bg_img;
    std::getline(file,bg_img,'\n');
    m_buffer.m_bg_img = bg_img;
}

void Save::ReadSaveFile(std::ifstream &file)
{
    std::string value;
    std::getline(file,value,'\n');
    m_user_data.script_line = std::stoi(value);
    std::getline(file,value,'\n');
    m_user_data.nb_dial = std::stoi(value);
}

void Save::SaveBuffer(std::ofstream &file) const
{
    file << m_buffer.m_on_screen.size() << '\n';
    for (const auto & on_screen : m_buffer.m_on_screen)
    {
        file << on_screen.first << ' ' << on_screen.second.m_x << ' ' << on_screen.second.m_y << '\n';
    }
    file << m_buffer.m_previous_dialogue.size() << '\n';
    for (const auto & dial : m_buffer.m_previous_dialogue)
    {
        file << dial.first << '\n'
             << dial.second << '\n';
    }
    file << m_buffer.nb_current_dial << '\n';
    file << m_buffer.tm << '\n';
    file << m_buffer.m_bg_img << '\n';
}

void Save::SaveSaveData(std::ofstream &file) const
{
    file << m_user_data.script_line << '\n'
         << m_user_data.nb_dial << '\n';
}

void Save::AddDialogueToBuffer(const Dialogue &dial)
{
    std::string char_name = dial.m_talking->GetName();
    m_buffer.m_previous_dialogue.push_front(std::pair<std::string,std::string>(char_name,dial.m_text));
}

std::pair<std::string, std::string> & Save::GetLastDialogue()
{
    return m_buffer.m_previous_dialogue.back();
}

void Save::AddOnScreenToBuffer(const std::string & img_path, Point coord)
{
    m_buffer.m_on_screen.emplace(std::pair<std::string,Point>(img_path,coord));
}

void Save::UpdateScriptPos(int nb_lines)
{
    m_user_data.nb_dial++;
    m_user_data.script_line += nb_lines;
    m_buffer.nb_current_dial++;
}

void Save::UpdateBackground(const std::string &bg_path)
{
    m_buffer.m_bg_img = bg_path;
}

void Save::ClearCurrentDial()
{
    m_buffer.nb_current_dial = 0;
}

void Save::SetTextMode(text_mode txt_mode)
{
    m_buffer.tm = txt_mode;
}

text_mode Save::GetTextMode()
{
    return m_buffer.tm;
}

long long Save::GetScriptLine()
{
    return m_user_data.script_line;
}

const std::string &Save::GetBgPath()
{
    return m_buffer.m_bg_img;
}

unsigned short Save::GetNbCurrentDial()
{
    return m_buffer.nb_current_dial;
}

std::list<std::pair<std::string, std::string>> & Save::GetDialogues()
{
    return m_buffer.m_previous_dialogue;
}

std::map<std::string, Point> &Save::GetOnScreen()
{
    return m_buffer.m_on_screen;
}
