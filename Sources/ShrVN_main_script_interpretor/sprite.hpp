#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <list>
#include <ios>

#include "point.hpp"

class Sprite
{
    SDL_Rect m_position;
    SDL_Texture * m_texture;
    std::list<Point> * m_movement;
public:
    Sprite(SDL_Rect pos, SDL_Texture * texture);
    int RenderSprite(SDL_Renderer * rend);
    void SetMovement(std::list<Point> & pts);
    const SDL_Rect & GetPos() const;
    SDL_Texture * GetTexture() const;
};

std::ostream & operator<<(std::ostream & os, Sprite & spr);

std::ostream & operator<<(std::ostream & os, std::list<Sprite> lspr);

#endif // SPRITE_HPP
