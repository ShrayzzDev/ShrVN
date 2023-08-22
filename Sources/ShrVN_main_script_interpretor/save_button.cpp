#include <iostream>

#include "parserer_utils.h"
#include "save_button.h"
#include "window.hpp"
#include "font.h"
#include "save.h"

using namespace button;

std::ostream & operator<<(std::ostream & os, SDL_Rect rect)
{
    os << "x:" << rect.x << std::endl
       << "y:" << rect.y << std::endl
       << "w:" << rect.w << std::endl
       << "h:" << rect.h << std::endl;
    return os;
}

SaveButton::SaveButton(SDL_Rect rect)
    :m_preview{nullptr}, m_last_char_name{nullptr}, m_last_dialogue{nullptr}, m_rect{rect}, m_save{nullptr}, m_no_save_font{nullptr}, m_char_name_font{nullptr}, m_dial_font{nullptr}
{
#ifdef _WIN64
    m_no_save_font = CreateFont("calibri",70);
    m_char_name_font = CreateFont("calibri",30);
    m_dial_font = CreateFont("calibri",20);
#elif __linux__
    m_no_save_font = CreateFont("NotoSerif-CondensedLightItalic",70);
    m_char_name_font = CreateFont("NotoSerif-CondensedLightItalic",30);
    m_dial_font = CreateFont("NotoSerif-CondensedLightItalic",20);
#endif
}

void SaveButton::RenderBtn(SDL_Renderer *rend, short mouse_x, short mouse_y)
{
    if (m_last_dialogue != nullptr)
    {
        SDL_DestroyTexture(m_last_dialogue);
    }
    SDL_SetRenderDrawColor(rend,105,105,105,255);
    SDL_RenderFillRect(rend,&m_rect);
    if (m_save == nullptr)
    {
        SDL_Color color = {255,255,255,255};
        SDL_Surface * surf;
        surf = TTF_RenderText_Solid(m_no_save_font,"No Save",color);
        m_last_dialogue = SDL_CreateTextureFromSurface(rend,surf);
        SDL_RenderCopy(rend,m_last_dialogue,NULL,&m_rect);
        SDL_FreeSurface(surf);
    }
    else
    {
        SDL_Rect rect;
        rect = {m_rect.x + m_rect.w/2 + 5,m_rect.y + 3, m_rect.w/2 - 5, m_rect.h/4};
        SDL_RenderCopy(rend,m_last_char_name,NULL,&rect);
        rect.y += rect.h;
        rect.h = m_rect.h - rect.h;
        SDL_Color color = {0,0,0,255};
        SDL_Surface * surf = TTF_RenderText_Solid_Wrapped(m_dial_font,m_save->GetLastDialogue().second.c_str(),color,rect.w);
        if (m_last_dialogue != nullptr)
        {
            SDL_DestroyTexture(m_last_dialogue);
        }
        m_last_dialogue = SDL_CreateTextureFromSurface(rend,surf);
        SDL_QueryTexture(m_last_dialogue,NULL,NULL,NULL,&rect.h);
        SDL_RenderCopy(rend,m_last_dialogue,NULL,&rect);
        SDL_FreeSurface(surf);
    }
    if (m_preview != nullptr)
    {
        SDL_Rect rect = {m_rect.x + 3,m_rect.y + 3, m_rect.w/2 - 6, m_rect.h - 6};
        SDL_RenderCopy(rend,m_preview,NULL,&rect);
    }
    if (IsWithinBound(mouse_x,mouse_y))
    {
        SDL_Rect rect;
        rect = {m_rect.x - 20, m_rect.y - 20, m_rect.w + 40, m_rect.h + 40};
        SDL_SetRenderDrawColor(rend,255,255,255,100);
        SDL_RenderFillRect(rend,&rect);
    }
}

bool SaveButton::IsWithinBound(short x, short y)
{
    if ((x < m_rect.x) || (x > m_rect.x + m_rect.w) || (y < m_rect.y) || (y > m_rect.y + m_rect.h))
    {
        return false;
    }
    return true;
}

void SaveButton::SetSave(Save * save, SDL_Renderer * rend)
{
    if (m_save != nullptr)
    {
        SDL_DestroyTexture(m_last_char_name);
        m_last_char_name = nullptr;
        SDL_DestroyTexture(m_last_dialogue);
        m_last_dialogue = nullptr;
    }
    if (save == nullptr)
    {
        return;
    }
    m_save = save;
    std::pair<std::string,std::string> last_dial = m_save->GetLastDialogue();
    SDL_Color color = {0,0,0,255};
    SDL_Surface * surf;
    surf = TTF_RenderText_Solid(m_char_name_font,last_dial.first.c_str(),color);
    m_last_char_name = SDL_CreateTextureFromSurface(rend,surf);
    SDL_FreeSurface(surf);
}

void SaveButton::LoadImage(short save_slot, short save_page, Window * win)
{
    if (m_preview != nullptr)
    {
        SDL_DestroyTexture(m_preview);
        m_preview = nullptr;
    }
    if (save_slot == -1)
    {
        m_save = nullptr;
        return;
    }
    SDL_Surface * surf;
    std::string save_folder;
    save_folder += GetSaveDataFolder(win->GetName()) + "/savedata/" + std::to_string(save_page) + "/" + std::to_string(save_slot) + ".bmp";
    surf = SDL_LoadBMP(save_folder.c_str());
    m_preview = SDL_CreateTextureFromSurface(win->GetRenderer(),surf);
    SDL_FreeSurface(surf);
}
