#include <filesystem>
#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "button.hpp"
#include "font.h"

Button::Button(const std::string & name, const std::string &texture_path, SDL_Rect rect, SDL_Renderer * rend)
    :m_name{name}, m_title{nullptr}, m_rect{rect}, m_font{nullptr}, IsTextTexture{false}
{
    std::string full_path = "images/" + texture_path;
    if (!std::filesystem::exists(full_path))
    {
        throw std::invalid_argument("ERROR : couldn't find texture : " + texture_path + " to create a button");
    }
    m_texture = IMG_LoadTexture(rend,full_path.c_str());
#ifdef _WIN64
    m_font = CreateFont("calibri",120);
#elif __linux__
    m_font = CreateFont("NotoSerif-CondensedLightItalic",120);
#endif
}

Button::Button(const std::string &name, const std::string &text, SDL_Color rect_col, SDL_Rect rect, SDL_Renderer *rend)
    :m_name{name}, m_title{nullptr}, m_rect{rect}, m_color{rect_col}, IsTextTexture{true}
{
    SDL_Color text_col = {0,0,0,255};
#ifdef _WIN64
    m_font = CreateFont("calibri",120);
#elif __linux__
    m_font = CreateFont("NotoSerif-CondensedLightItalic",120);
#endif
    SDL_Surface * surf;
    surf = TTF_RenderText_Solid(m_font,text.c_str(),text_col);
    m_texture = SDL_CreateTextureFromSurface(rend,surf);
    m_rect = {rect.x, rect.y - (rect.h+20), rect.w + 20, rect.h + 20};
}

long long pas_joli = 0;
void Button::RenderButton(SDL_Renderer *rend, short mouse_x, short mouse_y, bool show_title)
{
    if (IsWithinBound(mouse_x,mouse_y))
    {
        SDL_SetRenderDrawColor(rend,255,255,255,50);
        SDL_RenderFillRect(rend,&m_rect);
    }
    if (IsTextTexture)
    {
        SDL_SetRenderDrawColor(rend,m_color.r,m_color.g,m_color.b,m_color.a);
        SDL_RenderFillRect(rend,&m_rect);
        SDL_SetRenderDrawColor(rend,0,0,0,255);
        SDL_RenderDrawRect(rend,&m_rect);
    }
    if (show_title)
    {
        if (m_title == nullptr)
        {
            SDL_Color color = {0,0,0,255};
            SDL_Surface * surf;
            surf = TTF_RenderText_Solid(m_font,m_name.c_str(),color);
            m_title = SDL_CreateTextureFromSurface(rend,surf);
            SDL_FreeSurface(surf);
        }
        SDL_Rect rect = {m_rect.x, m_rect.y + m_rect.h, m_rect.w,60};
        SDL_RenderCopy(rend,m_title,NULL,&rect);
    }
    SDL_RenderCopy(rend,m_texture,NULL,&m_rect);
}

bool Button::IsWithinBound(short x, short y)
{
    if ((x < m_rect.x) || (x > m_rect.x + m_rect.w) || (y < m_rect.y) || (y > m_rect.y + m_rect.h))
    {
        return false;
    }
    return true;
}

Point Button::GetMiddle()
{
    Point pt;
    pt.m_x = m_rect.x + m_rect.w/2;
    pt.m_y = m_rect.y + m_rect.h/2;
    return pt;
}
