#ifndef CURRENTSCREEN_H
#define CURRENTSCREEN_H

#include <list>
#include <string>

#include <SDL.h>

class Window;

class Button;

class CurrentScreen
{
public:
    virtual void ReactEvent(Window * win, SDL_Event & event) = 0;
    virtual void RenderWindow(SDL_Renderer * rend, unsigned short window_length, unsigned short window_height) = 0;
};

#endif // CURRENTSCREEN_H
