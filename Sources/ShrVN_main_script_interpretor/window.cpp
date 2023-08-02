#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "window.hpp"
#include "initialisation_error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Window::Window(const std::string & name, unsigned short height, unsigned short length, InGameOverlayParameters * igop, OptionsMenuParameters * omp, InGameMenuParameters * igmp, SavesMenuParameters * smp, MainMenuParameters * mmp)
    : m_name{name}, m_height{height}, m_length{length}, m_open{true}, m_omp{omp}, m_igmp{igmp}, m_smp{smp}, m_mmp{mmp}, IsClicked{false}
{
    SetInGameOverlayParameters(igop);
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
    if (TTF_Init() != 0)
    {
        std::string error = "ERROR : Couldn't initialize the font component: " + (std::string)SDL_GetError();
        throw Initialisation_Error(error.c_str());
    }
    SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);
    SDL_Color color = {0,0,0,255};

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

InGameWindow & Window::GetIgw()
{
    return m_igw;
}

void Window::SetInGameOverlayParameters(InGameOverlayParameters * igop)
{
    if (m_igw.GetIgop() != nullptr)
    {
        SDL_DestroyTexture(m_igw.GetBgImg());
    }
    InGameWindow igw = {igop};
    m_igw = igw;
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

void Window::SetCurrentScreen(CurrentScreen current)
{
    m_current = current;
}

void Window::ReactEvent()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_MAXIMIZED:
                m_length = 1920;
                m_height = 1080;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                m_open = false;
                this->~Window();
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.clicks) {
            case SDL_BUTTON_LEFT:
                Click();
                break;
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_RETURN:
                Click();
                break;
            }
            break;
        }
    }
}

Window::~Window()
{
    SDL_DestroyTexture(m_igw.GetBgImg());
    m_igw.DestroyDialogues();
    m_igw.DestroyOnScreenSprite();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::IsOpen() const
{
    return m_open;
}

void Window::RenderImage()
{
    SDL_RenderClear(m_renderer);
    switch (m_current) {
    case InGame:
    {
        m_igw.RenderWindow(m_renderer,m_length,m_height);
    }
    }
    SDL_RenderPresent(m_renderer);
}

void Window::Click()
{
    IsClicked = true;
    switch (m_current) {
    case InGame:
        m_igw.Click();
    }
}

void Window::InitFont()
{
    m_igw.SetFont();
}

std::ostream & operator<<(std::ostream & os, Window win)
{
    return os << "Name: " << win.GetName() << std::endl
              << "Height" << win.GetHeight() << std::endl
              << "Length" << win.GetLength() << std::endl;
}
