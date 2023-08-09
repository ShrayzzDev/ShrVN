#ifndef INTERPRETEDSAVELOADER_HPP
#define INTERPRETEDSAVELOADER_HPP

#include "ISaveLoader.hpp"

class InterpretedSaveLoader : public ISaveLoader
{
public:
    void LoadSave(InGameWindow *igw, Save save) const override;
};

#endif // INTERPRETEDSAVELOADER_HPP
