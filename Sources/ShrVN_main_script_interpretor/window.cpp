#include <filesystem>
#include <iostream>

#include "window.hpp"
#include "initialisation_error.hpp"

#include <SDL.h>
#include <SDL_image.h>

Window::Window(const std::string & name, unsigned short height, unsigned short length, InGameOverlayParameters * igop, OptionsMenuParameters * omp, InGameMenuParameters * igmp, SavesMenuParameters * smp, MainMenuParameters * mmp)
    : m_name{name}, m_height{height}, m_length{length}, m_open{true}, m_igop{igop}, m_omp{omp}, m_igmp{igmp}, m_smp{smp}, m_mmp{mmp}, m_onscreen_sprites{}
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

SDL_Renderer * Window::GetRenderer() const
{
    return m_renderer;
}

Sprite *Window::GetSprite(const std::string &img_path)
{
    return &m_onscreen_sprites.at(img_path);
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

void Window::SetInGameOverlayParameters(InGameOverlayParameters * igop)
{
    m_igop = igop;
}

void Window::SetOptionsMenuParameters(OptionsMenuParameters * omp)
{
    m_omp = omp;
}

void Window::SetInGameMenuParameters(InGameMenuParameters * igmp)
{
    m_igmp = igmp;
}

void Window::SetSavesMenuParameters(SavesMenuParameters * smp)
{
    m_smp = smp;
}

void Window::SetMainMenuParameters(MainMenuParameters * mmp)
{
    m_mmp = mmp;
}

void Window::AddOnScreenSprite(const std::string &image_path, Point coord, SDL_Texture *texture)
{
    SDL_Rect rect;
    rect.x = coord.m_x;
    rect.y = coord.m_y;
    if (texture == nullptr)
    {
        std::filesystem::path full_path = std::filesystem::current_path().generic_string() + "/images/" + image_path;
        if (! std::filesystem::exists(full_path))
        {
            throw std::invalid_argument("ERROR : Couldn't find the " + image_path);
        }
        SDL_Texture * new_texture = IMG_LoadTexture(m_renderer,full_path.generic_string().c_str());
        if (new_texture == nullptr)
        {
            std::cerr << "Couldn't create a texture" << std::endl;
        }
        SDL_QueryTexture(new_texture,NULL,NULL,&rect.w,&rect.h);
        Sprite current_sprite(rect,new_texture);
        m_onscreen_sprites.insert(std::pair(image_path,current_sprite));
        return;
    }
    SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);
    Sprite current_sprite = {rect,texture};
    m_onscreen_sprites.insert(std::pair(image_path,current_sprite));
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
                        break;
                    }
                }
                break;
        }
    }
}

Window::~Window()
{
    SDL_DestroyTexture(m_background_img);
    for (auto & sprite : m_onscreen_sprites)
    {
        SDL_DestroyTexture(sprite.second.GetTexture());
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::IsOpen()
{
    return m_open;
}

void Window::RenderImage()
{
    int i = 1;
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,m_background_img,NULL,NULL);
    for (auto & sprite : m_onscreen_sprites)
    {
        if (sprite.second.RenderSprite(m_renderer))
        {
            std::cerr << "Error while rendering image : " << SDL_GetError() << std::endl;
        }
    }
    SDL_RenderPresent(m_renderer);
}


std::ostream & operator<<(std::ostream & os, Window win)
{
    return os << "Name: " << win.GetName() << std::endl
              << "Height" << win.GetHeight() << std::endl
              << "Length" << win.GetLength() << std::endl;
}
