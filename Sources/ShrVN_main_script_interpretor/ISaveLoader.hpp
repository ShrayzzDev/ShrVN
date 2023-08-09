#ifndef ISAVELOADER_HPP
#define ISAVELOADER_HPP

class InGameWindow;

class Save;

class ISaveLoader
{
public:
    virtual void LoadSave(InGameWindow * igw, Save save) const = 0;
};

#endif // ISAVELOADER_HPP
