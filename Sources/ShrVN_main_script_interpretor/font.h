#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

TTF_Font * CreateFont(const std::string & font_type, unsigned short font_size);

#endif // FONT_H
