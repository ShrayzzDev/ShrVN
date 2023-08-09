#include "save_button.h"
#include "font.h"
#include "save.h"
#include <iostream>

using namespace button;

SaveButton::SaveButton(SDL_Rect rect, Save * save)
    :m_preview{nullptr}, m_last_char_name{nullptr}, m_last_dialogue{nullptr}, m_rect{rect}, m_save{save}, m_font{nullptr}
{
#ifdef _WIN64
    m_font = CreateFont("calibri",400);
#elif __linux__
    m_font = CreateFont("NotoSerif-CondensedLightItalic",400);
#endif
    if (save == nullptr)
    {
        return;
    }
}

void SaveButton::RenderBtn(SDL_Renderer *rend)
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
        surf = TTF_RenderText_Solid(m_font,"No Save",color);
        m_last_dialogue = SDL_CreateTextureFromSurface(rend,surf);
        SDL_RenderCopy(rend,m_last_dialogue,NULL,&m_rect);
        SDL_FreeSurface(surf);
    }
    else
    {
        SDL_Rect rect;
        rect = {m_rect.x + m_rect.w/2 + 5,m_rect.y + 3, m_rect.w/2 - 5, m_rect.h/4};
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
    if (save == nullptr)
    {
        return;
    }
    if (m_save != nullptr)
    {
        SDL_DestroyTexture(m_last_char_name);
        SDL_DestroyTexture(m_last_dialogue);
        SDL_DestroyTexture(m_preview);
    }
    m_save = save;
    std::pair<std::string,std::string> last_dial = m_save->GetLastDialogue();
    SDL_Color color = {0,0,0,255};
    SDL_Surface * surf;
    surf = TTF_RenderText_Solid(m_font,last_dial.first.c_str(),color);
    m_last_char_name = SDL_CreateTextureFromSurface(rend,surf);
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Solid(m_font,last_dial.second.c_str(),color);
    m_last_dialogue = SDL_CreateTextureFromSurface(rend,surf);
    SDL_FreeSurface(surf);
}
