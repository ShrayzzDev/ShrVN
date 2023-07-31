#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>

#include <SDL.h>

#include "characters.hpp"

struct Dialogue
{
    SDL_Texture * m_text;
    Characters * m_talking;
    SDL_Rect m_rect;
};

#endif // DIALOGUE_H
