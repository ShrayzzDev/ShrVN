#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "window.hpp"
#include "initialisation_error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Window::Window(const std::string & name, unsigned short height, unsigned short length, ISaveLoader * isl, InGameOverlayParameters * igop, OptionsMenuParameters * omp, InGameMenuParameters * igmp, SavesMenuParameters * smp, MainMenuParameters * mmp, std::map<std::string,Characters> * char_map)
    : m_name{name}, m_height{height}, m_length{length}, m_open{true}, m_char_map{char_map}, m_omp{omp}, m_mmp{mmp}, m_screenshot{nullptr}, IsClicked{false}
{
    SetInGame(isl,igop,igmp);
    SetSaveScreen(smp);
    m_current = &m_igw;
}

void Window::Init(std::ifstream & script)
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
    m_igw.InitButtons(m_renderer);
    m_igw.SetCurrentScript(&script);
    m_sw.InitScreen(m_renderer,this);
    m_sw.GetCurrentSave().SetTextMode(ADV);
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

std::map<std::string, Characters> *Window::GetCharMap()
{
    return m_char_map;
}

InGameWindow & Window::GetIgw()
{
    return m_igw;
}

SaveScreen &Window::GetSc()
{
    return m_sw;
}

void Window::TakeScreenShot()
{
    const int format = SDL_PIXELFORMAT_ARGB8888;
    if (m_screenshot != nullptr)
    {
        SDL_FreeSurface(m_screenshot);
    }
    m_screenshot = SDL_CreateRGBSurfaceWithFormat(0, m_length, m_height, 32, format);
    SDL_RenderReadPixels(m_renderer, NULL, format, m_screenshot->pixels, m_screenshot->pitch);
}

void Window::SaveScreenShot(const std::string &file_name, const std::string &file_path)
{
    std::filesystem::path old_path = std::filesystem::current_path();
    std::filesystem::current_path(file_path);
    SDL_SaveBMP(m_screenshot,(file_name + ".bmp").c_str());
    std::filesystem::current_path(old_path);
}

void Window::SetInGame(ISaveLoader * isl, InGameOverlayParameters * igop, InGameMenuParameters * igmp)
{
    if (m_igw.GetIgop() != nullptr)
    {
        SDL_DestroyTexture(m_igw.GetBgImg());
    }
    InGameWindow igw = {isl,igop,igmp};
    SDL_Color color = {0,0,0,0};
    igw.SetTextColor(color);
    m_igw = igw;
}

void Window::SetSaveScreen(SavesMenuParameters *smp)
{
    if (m_sw.GetSmp() != nullptr)
    {
        SDL_DestroyTexture(m_sw.GetBgImg());
    }
    SaveScreen sw = {smp};
    m_sw = sw;
}

void Window::SetOptionsMenuParameters(OptionsMenuParameters * omp)
{
    m_omp = omp;
}

void Window::SetMainMenuParameters(MainMenuParameters * mmp)
{
    m_mmp = mmp;
}

void Window::SetCurrentScreen(CurrentScreenEnum cs)
{
    switch(cs){
    case in_game:
        m_current = &m_igw;
        break;
    case save:
        m_sw.SetMenuState(Saving);
        m_current = &m_sw;
        break;
    case load:
        m_sw.SetMenuState(Loading);
        m_current = &m_sw;
        break;
    }
}

void Window::AddSpriteToBuffer(const std::string &img_path, Point coord)
{
    m_sw.m_current_save.AddOnScreenToBuffer(img_path,coord);
}

void Window::Maximize()
{
    m_length = 1920;
    m_height = 1080;
}

void Window::UpdateSave(int nb_line, const Dialogue &dial)
{
    m_sw.m_current_save.UpdateScriptPos(nb_line);
    m_sw.m_current_save.AddDialogueToBuffer(dial);
}

void Window::UpdateBackground(const std::string &img_path)
{
    m_igw.SetBackgroundImg(img_path,m_renderer);
    m_sw.GetCurrentSave().UpdateBackground(img_path);
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
    m_current->RenderWindow(m_renderer,m_length,m_height);
    SDL_RenderPresent(m_renderer);
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
                Maximize();
                break;

            case SDL_WINDOWEVENT_CLOSE:
                exit(0);
                break;
            }
        default:
            m_current->ReactEvent(this,event);
            break;
        }
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
