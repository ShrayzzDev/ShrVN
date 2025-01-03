#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <list>
#include <ios>
#include <mutex>
#include <thread>

#include "point.hpp"
#include "movement.h"
#include "observableobject.h"

class Sprite : public ObservableObject
{
    SDL_Rect m_position;
    SDL_Texture * m_texture;
    std::list<Point> * m_movement;
public:
    Sprite(SDL_Rect pos, SDL_Texture * texture);
    int RenderSprite(SDL_Renderer * rend);
    void SetMovement(Movement & mv, unsigned int nb_pts, SDL_Renderer * rend);
    const SDL_Rect & GetPos() const;
    SDL_Texture * GetTexture() const;
    void block_thread_while_locked() const;
    bool IsMovementEmpty();
    void SetPosToLastMovement();
    void ClearMovement();
    void ReactEvent() override;
};

std::ostream & operator<<(std::ostream & os, Sprite & spr);

std::ostream & operator<<(std::ostream & os, std::list<Sprite> lspr);

#endif // SPRITE_HPP
