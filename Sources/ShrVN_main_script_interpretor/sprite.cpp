#include "sprite.hpp"
#include "bezier.h"
#include "SDL.h"

#include <iostream>
#include <thread>
#include <chrono>

Sprite::Sprite(SDL_Rect pos, SDL_Texture * texture)
    : m_position{pos}, m_texture{texture}, m_movement{nullptr}
{

}

using namespace std::chrono_literals;

std::mutex m_movement_lock;

int Sprite::RenderSprite(SDL_Renderer *rend)
{
    return SDL_RenderCopy(rend,m_texture,NULL,&m_position);
}

void Sprite::block_thread_while_locked() const
{
    while(!m_movement_lock.try_lock())
    {
        std::this_thread::sleep_for(1ms);
    }
}


void Sprite::SetMovement(Movement & mv, unsigned int nb_pts, SDL_Renderer * rend)
{
    // if (m_movement != nullptr)
    // {
    //     free(m_movement);
    // }
    // std::list<Point> * pts = new std::list<Point>(CalculateAllBezierPoint(mv.control_points,nb_pts));
    // m_movement = pts;
    // std::thread thread([](std::list<Point> *pts, Sprite * sprite) {
    //     int pos = 0;
    //     for (auto & pt : *pts)
    //     {
    //         std::cout << "je suis ici: " << pos << std::endl;
    //         // std::this_thread::sleep_for(10ms);
    //         std::cout << "je suis content" << std::endl;
    //         sprite->block_thread_while_locked();
    //         std::cout << "je suis content" << std::endl;
    //         sprite->m_position.x = pt.m_x;
    //         sprite->m_position.y = pt.m_y;
    //         sprite->m_movement->pop_front();
    //         std::cout << "ah ?" << std::endl;
    //         std::cout << sprite->m_position.x << " : " << sprite->m_position.y << std::endl;
    //         sprite->Notify();
    //         m_movement_lock.unlock();
    //         pos++;
    //     }
    // }, m_movement, this);
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
    // block_thread_while_locked();
    if (m_movement == nullptr)
    {
        return true;
    }
    return m_movement->empty();
}

void Sprite::SetPosToLastMovement()
{
    // block_thread_while_locked();
    m_position.x = m_movement->back().m_x;
    m_position.y = m_movement->back().m_y;
    Notify();
    m_movement_lock.unlock();
}

void Sprite::ClearMovement()
{
    block_thread_while_locked();
    free(m_movement);
    m_movement = nullptr;
    Notify();
    m_movement_lock.unlock();
}

void Sprite::ReactEvent()
{

}
