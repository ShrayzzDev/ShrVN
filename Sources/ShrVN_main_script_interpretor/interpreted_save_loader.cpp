#include <iostream>
#include <string>

#include "interpreted_save_loader.hpp"
#include "in_game_window.hpp"
#include "save.h"

void InterpretedSaveLoader::LoadSave(std::ifstream & file, InGameWindow * igw, Save save, unsigned short current_line, std::map<std::string,Characters> char_map, SDL_Renderer * rend) const
{
    std::string temp;
    for (int i = 0; i < save.GetScriptLine() - current_line; ++i)
    {
        std::getline(file,temp);
    }
    igw->CleanCurrentMessages();
    igw->SetTextMode(save.GetTextMode());
    for (auto & dia : save.GetDialogues())
    {
        Dialogue dial;
        for (auto & character : char_map)
        {
            if (character.second.GetName() == dia.first)
            {
                dial = igw->CreateDialogue(dia.second,character.second,rend);
                break;
            }
        }
        igw->AddPreviousDialogue(dial);
    }
    int i = 0;
    for (auto & dial : igw->GetPreviousDialogue())
    {
        if (i == save.GetNbCurrentDial())
        {
            break;
        }
        igw->AddCurrentDialogue(dial);
        ++i;
    }
}
