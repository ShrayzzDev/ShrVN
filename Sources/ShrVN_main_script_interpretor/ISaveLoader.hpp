#ifndef ISAVELOADER_HPP
#define ISAVELOADER_HPP

#include <fstream>
#include <map>

class InGameWindow;

class Save;

class Characters;

class ISaveLoader
{
public:
    virtual void LoadSave(std::ifstream & file, InGameWindow * igw, Save save, std::map<std::string,Characters> char_map, SDL_Renderer * rend) const = 0;
};

#endif // ISAVELOADER_HPP
