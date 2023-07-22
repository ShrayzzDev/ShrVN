#include <filesystem>
#include <iostream>

#include "window.hpp"
#include "initialisation_error.hpp"

#include <SDL_image.h>

Window::Window(const std::string & name, unsigned short height, unsigned short length)
    : m_name{name}, m_height{height}, m_length{length}
{

}

void Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::string error = "ERROR : Couldn't initialize video component: " + (std::string)SDL_GetError();
        throw Initialisation_Error(error.c_str());
    }
    m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_length, m_height, SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr)
    {
        std::string error = "ERROR : Couldn't create a window: " + (std::string)SDL_GetError();
        throw Initialisation_Error(error.c_str());
    }
    SDL_SetWindowTitle(m_window,m_name.c_str());
    m_renderer = SDL_CreateRenderer(m_window, -1,SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        std::string error = "ERROR : Couldn't create a window renderer: " + (std::string)SDL_GetError();
        throw Initialisation_Error(error.c_str());
    }
}

const std::string & Window::GetName() const
{
    return m_name;
}

unsigned short Window::GetHeight() const
{
    return m_height;
}

unsigned short Window::GetLength() const
{
    return m_length;
}

SDL_Renderer *Window::GetRenderer() const
{
    return m_renderer;
}

void Window::SetBackgroundImg(const std::string &bg_img)
{
    std::filesystem::path full_path = std::filesystem::current_path().generic_string() + "/images/" + bg_img;
    if (! std::filesystem::exists(full_path))
    {
        throw std::invalid_argument("ERROR : Couldn't find the " + bg_img);
    }
    m_background_img = IMG_LoadTexture(m_renderer,full_path.generic_string().c_str());
    if (m_background_img == nullptr)
    {
        throw std::invalid_argument("ERROR : Couldn't open file " + bg_img);
    }
}

void Window::ReactEvent()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_MAXIMIZED:
                    {
                        m_length = 1920;
                        m_height = 1080;
                        break;
                    }
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        m_open = false;
                        this->~Window();
                    }
                }
        }
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_background_img);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::IsOpen()
{
    return m_open;
}

void Window::RenderImage()
{
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,m_background_img,NULL,NULL);
    SDL_RenderPresent(m_renderer);
}


std::ostream & operator<<(std::ostream & os, Window win)
{
    return os << "Name: " << win.GetName() << std::endl
              << "Height" << win.GetHeight() << std::endl
              << "Length" << win.GetLength() << std::endl;
}
