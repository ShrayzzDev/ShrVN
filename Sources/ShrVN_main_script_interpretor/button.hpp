#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL.h>
#include <string>

#include "point.hpp"

class Window;

class Button
{
    std::string m_name;
    SDL_Texture * m_texture;
    SDL_Rect m_rect;
    SDL_Color m_color;
public:
    Button(const std::string & name, const std::string & texture_path, unsigned short length, unsigned short height, short x_coord, short y_coord, SDL_Renderer * rend);
    void (*m_WhenPressed)(Window*) = nullptr;
    void RenderButton(SDL_Renderer * rend, short mouse_x, short mouse_y);
    bool IsWithinBound(short x, short y);
    Point GetMiddle();
};

#endif // BUTTON_HPP
