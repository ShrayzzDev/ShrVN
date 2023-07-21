#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

using namespace std;

void SDLInit()
{
    if(! SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << "c'est bon bg" << endl;
    }
    else
    {
        cout << SDL_GetError() << endl;
    }
}

int main()
{
    SDLInit();
    return 0;
}
