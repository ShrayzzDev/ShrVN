#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "point.hpp"

class Window;

class CurrentScreen;

class Button
{
    std::string m_name;
    SDL_Texture * m_texture;
    SDL_Rect m_rect;
    SDL_Color m_color;
    TTF_Font * m_font;
    bool IsTextTexture;
public:
    Button(const std::string & name, const std::string & texture_path, SDL_Rect rect, SDL_Renderer * rend);
    Button(const std::string & name, const std::string & text, SDL_Color rect_col, SDL_Rect rect, SDL_Renderer * rend);
    void (*m_WhenPressed)(Window*,CurrentScreen*) = nullptr;
    void RenderButton(SDL_Renderer * rend, short mouse_x, short mouse_y, bool show_title);
    bool IsWithinBound(short x, short y);
    SDL_Texture * m_title;
    Point GetMiddle();
};

#endif // BUTTON_HPP
