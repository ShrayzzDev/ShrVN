#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>

#include <string>
#include <ostream>

class Window
{
    std::string m_name;
    unsigned short m_height;
    unsigned short m_length;
    bool m_open;
    std::string m_background_img;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
public:
    Window(const std::string & name, unsigned short height = 1080, unsigned short length = 1920);
    void Init();
    const std::string & GetName() const;
    unsigned short GetHeight() const;
    unsigned short GetLength() const;
    SDL_Renderer * GetRenderer() const;
    void ReactEvent();
    bool IsOpen();
    ~Window();
};

std::ostream & operator<<(std::ostream & os, Window win);

#endif // WINDOW_HPP
