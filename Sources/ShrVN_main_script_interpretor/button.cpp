#include <filesystem>
#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "button.hpp"

Button::Button(const std::string & name, const std::string &texture_path, unsigned short length, unsigned short height, short x_coord, short y_coord, SDL_Renderer * rend)
    :m_name{name}, m_rect{x_coord,y_coord,length,height}
{
    std::string full_path = "images/" + texture_path;
    if (!std::filesystem::exists(full_path))
    {
        throw std::invalid_argument("ERROR : couldn't find texture : " + texture_path + " to create a button");
    }
    m_texture = IMG_LoadTexture(rend,full_path.c_str());
}

void Button::RenderButton(SDL_Renderer *rend, short mouse_x, short mouse_y)
{
    if (IsWithinBound(mouse_x,mouse_y))
    {
        SDL_SetRenderDrawColor(rend,255,255,255,50);
        SDL_RenderFillRect(rend,&m_rect);
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
