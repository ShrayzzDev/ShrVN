#include <iostream>

#include "save.h"

Save::Save()
{

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
    return m_buffer.m_previous_dialogue.front();
}

void Save::AddOnScreenToBuffer(const std::string & img_path, Point coord)
{
    m_buffer.m_on_screen.emplace(std::pair<std::string,Point>(img_path,coord));
}

void Save::UpdateScriptPos(int nb_lines)
{
    m_user_data.nb_dial++;
    m_user_data.script_line += nb_lines;
}
