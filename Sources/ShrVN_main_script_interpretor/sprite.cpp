#include "sprite.hpp"

#include <iostream>

Sprite::Sprite(SDL_Rect pos, SDL_Texture * texture)
    :m_position{pos}, m_texture{texture}, m_movement{nullptr}
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

void Sprite::SetMovement(std::list<Point> &pts)
{
    m_movement = &pts;
}

const SDL_Rect & Sprite::GetPos() const
{
    return m_position;
}

SDL_Texture *Sprite::GetTexture() const
{
    return m_texture;
}
