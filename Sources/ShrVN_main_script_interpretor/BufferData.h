#ifndef BUFFERDATA_H
#define BUFFERDATA_H

#include <map>
#include <list>
#include <string>

#include "point.hpp"

struct BufferData
{
    std::map<std::string,Point> m_on_screen;
    std::string m_bg_img;
    std::list<std::pair<std::string,std::string>> m_previous_dialogue;
};

#endif // BUFFERDATA_H
