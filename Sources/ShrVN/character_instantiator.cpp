#include <filesystem>

#include "character_instantiator.hpp"

using namespace std;

CharacterInstantiator::CharacterInstantiator()
{

}

void CharacterInstantiator::AddChar(std::map<std::string, Characters> &Characters_map, const std::string &inst_name, const std::string &char_name, unsigned short red_value, unsigned short green_value, unsigned short blue_value) const
{
    Characters_map.emplace(inst_name, Characters(char_name,red_value,green_value,blue_value));
}

void CharacterInstantiator::AddImage(std::map<std::string, Characters> &Characters_map, const std::string & char_inst_name, const std::string &inst_name, const std::string &img_path) const
{
    string file_name = filesystem::path(img_path).filename().generic_string();
    string path_to_file = filesystem::path(img_path).parent_path().generic_string();
    Characters_map.at(char_inst_name).AddImage(inst_name,file_name,path_to_file);
}
