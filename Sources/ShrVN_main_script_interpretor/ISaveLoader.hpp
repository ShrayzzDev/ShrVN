#ifndef ISAVELOADER_HPP
#define ISAVELOADER_HPP

#include <fstream>
#include <map>

class InGameWindow;

class Save;

class Characters;

class Window;

class ISaveLoader
{
public:
    virtual void LoadSave(std::ifstream & file, InGameWindow * igw, Save save, unsigned short current_line, std::map<std::string,Characters> & char_map, Window * win) const = 0;
};

#endif // ISAVELOADER_HPP
