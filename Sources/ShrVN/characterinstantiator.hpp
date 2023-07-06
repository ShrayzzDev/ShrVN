#ifndef CHARACTERINSTANTIATOR_HPP
#define CHARACTERINSTANTIATOR_HPP

#include "icharacterinterpreter.hpp"

class CharacterInstantiator: virtual public ICharacterInterpreter
{
public:
    CharacterInstantiator();
    void AddChar(std::map<std::string, Characters> & Characters_map, const std::string & inst_name, const std::string & char_name, unsigned short red_value = 255, unsigned short green_value = 255, unsigned short blue_value = 255) const override;
    void AddImage(std::map<std::string, Characters> & Characters_map, const std::string & char_inst_name, const std::string & inst_name, const std::string & img_path) const override;
};

#endif // CHARACTERINSTANTIATOR_HPP
