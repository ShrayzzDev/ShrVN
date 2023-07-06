#ifndef ICHARACTERINTERPRETER_HPP
#define ICHARACTERINTERPRETER_HPP

#include <map>
#include <string>

#include "characters.hpp"

class ICharacterInterpreter
{
public:
    virtual void AddChar(std::map<std::string, Characters> & Characters_map, const std::string & inst_name, const std::string & char_name, unsigned short red_value = 255, unsigned short green_value = 255, unsigned short blue_value = 255) const = 0;
    virtual void AddImage(std::map<std::string, Characters> & Characters_map, const std::string & char_inst_name, const std::string & inst_name, const std::string & img_path) const = 0;
};

#endif // ICHARACTERINTERPRETER_HPP
