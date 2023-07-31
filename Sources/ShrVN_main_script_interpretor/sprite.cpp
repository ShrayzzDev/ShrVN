#include "sprite.hpp"
#include "bezier.h"

Sprite::Sprite(SDL_Rect pos, SDL_Texture * texture)
    : m_position{pos}, m_texture{texture}, m_movement{nullptr}
{

}

int Sprite::RenderSprite(SDL_Renderer *rend)
{
    if (m_movement != nullptr && !m_movement->empty())
    {
        m_position.x = m_movement->front().m_x;
        m_position.y = m_movement->front().m_y;
        m_movement->pop_front();
    }
    return SDL_RenderCopy(rend,m_texture,NULL,&m_position);
}

void Sprite::SetMovement(Movement & mv, unsigned int nb_pts)
{
    if (m_movement != nullptr)
    {
        free(m_movement);
    }
    std::list<Point> * pts = new std::list<Point>(CalculateAllBezierPoint(mv.control_points,nb_pts));
    m_movement = pts;
}

const SDL_Rect & Sprite::GetPos() const
{
    return m_position;
}

SDL_Texture *Sprite::GetTexture() const
{
    return m_texture;
}

bool Sprite::IsMovementEmpty()
{
    if (m_movement == nullptr)
    {
        return true;
    }
    return m_movement->empty();
}

void Sprite::SetPosToLastMovement()
{
    m_position.x = m_movement->back().m_x;
    m_position.y = m_movement->back().m_y;
}

void Sprite::ClearMovement()
{
    free(m_movement);
    m_movement = nullptr;
}
