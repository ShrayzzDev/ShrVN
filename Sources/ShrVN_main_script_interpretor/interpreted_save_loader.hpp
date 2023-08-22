#ifndef INTERPRETEDSAVELOADER_HPP
#define INTERPRETEDSAVELOADER_HPP

#include <map>
#include <string>

#include <SDL.h>

#include "ISaveLoader.hpp"
#include "characters.hpp"

class InterpretedSaveLoader : public ISaveLoader
{
public:
    void LoadSave(std::ifstream & file, InGameWindow * igw, Save save, unsigned short current_line, std::map<std::string,Characters> & char_map, Window * win) const override;
};

#endif // INTERPRETEDSAVELOADER_HPP
