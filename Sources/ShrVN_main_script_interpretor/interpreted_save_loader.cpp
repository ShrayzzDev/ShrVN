#include <iostream>
#include <string>

#include "interpreted_save_loader.hpp"
#include "in_game_window.hpp"
#include "window.hpp"
#include "save.h"

void InterpretedSaveLoader::LoadSave(std::ifstream & file, InGameWindow * igw, Save save, unsigned short current_line, std::map<std::string,Characters> char_map, Window * win) const
{
    std::string temp;
    for (int i = 0; i < save.GetScriptLine() - current_line; ++i)
    {
        std::getline(file,temp);
    }
    igw->CleanCurrentMessages();
    igw->CleanPreviousDialogue();
    igw->SetTextMode(save.GetTextMode());
    auto & dials = save.GetDialogues();
    for (auto it = dials.crbegin(); it != dials.crend(); ++it)
    {
        Dialogue dial;
        for (auto & character : char_map)
        {
            if (character.second.GetName() == it->first)
            {
                dial = igw->CreateDialogue(it->second,character.second,win->GetRenderer());
                break;
            }
        }
        igw->AddPreviousDialogue(dial);
    }
    int i = 1;
    for (auto & dial : igw->GetPreviousDialogue())
    {
        if (i == save.GetNbCurrentDial())
        {
            break;
        }
        igw->AddCurrentDialogueAtFront(dial);
        ++i;
    }
    for (auto & img : save.GetOnScreen())
    {
        igw->AddOnScreenSprite(img.first,img.second,win->GetRenderer(),nullptr);
    }
    win->UpdateBackground(save.GetBgPath());
}
