#include <iostream>
#include <string>

#include "interpreted_save_loader.hpp"
#include "in_game_window.hpp"
#include "window.hpp"
#include "save.h"

void InterpretedSaveLoader::LoadSave(std::ifstream & file, InGameWindow * igw, Save save, std::map<std::string,Characters> & char_map, Window * win) const
{
    std::string temp;
    file.seekg(0,std::ios::beg);
    file.seekg(save.GetScriptLine(),std::ios::beg);
    if (!file.good())
    {
        std::cout << "j'ai raté" << std::endl;
    }
    std::cout << save.GetScriptLine() << std::endl;
    std::cout << file.tellg() << std::endl;
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
    igw->CleanOnScreenSprites();
    for (auto & img : save.GetOnScreen())
    {
        igw->AddOnScreenSprite(img.first,img.second,win->GetRenderer(),nullptr);
    }
    win->UpdateBackground(save.GetBgPath());

}
