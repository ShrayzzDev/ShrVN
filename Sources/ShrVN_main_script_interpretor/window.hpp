#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <ostream>
#include <map>
#include <list>

#include "in_game_overlay_parameters.hpp"
#include "options_menu_parameters.hpp"
#include "in_game_menu_parameters.hpp"
#include "saves_menu_parameters.hpp"
#include "main_menu_parameters.hpp"
#include "CurrentScreen.h"
#include "sprite.hpp"
#include "in_game_window.hpp"

class Window
{
    std::string m_name;
    unsigned short m_height;
    unsigned short m_length;
    bool m_open;
    CurrentScreen * m_current;
    InGameWindow m_igw;
    OptionsMenuParameters * m_omp;
    InGameMenuParameters * m_igmp;
    SavesMenuParameters * m_smp;
    MainMenuParameters * m_mmp;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
public:
    Window(const std::string & name, unsigned short height = 1080, unsigned short length = 1920, InGameOverlayParameters * igop = nullptr, OptionsMenuParameters * omp = nullptr, InGameMenuParameters * igmp = nullptr, SavesMenuParameters * smp = nullptr, MainMenuParameters * mmp = nullptr);
    void Init();
    const std::string & GetName() const;
    unsigned short GetHeight() const;
    unsigned short GetLength() const;
    SDL_Renderer * GetRenderer() const;
    TTF_Font * GetFont() const;
    Sprite * GetSprite(const std::string & img_path);
    InGameWindow & GetIgw();
    void SetInGameOverlayParameters(InGameOverlayParameters * igop);
    void SetOptionsMenuParameters(OptionsMenuParameters * omp);
    void SetInGameMenuParameters(InGameMenuParameters * igmp);
    void SetSavesMenuParameters(SavesMenuParameters * smp);
    void SetMainMenuParameters(MainMenuParameters * mmp);
    void SetCurrentScreen(CurrentScreen * current);
    void Maximize();
    bool IsOpen() const;
    void ReactEvent();
    bool IsClicked;
    void RenderImage();
    void Click();
    void InitFont();
    ~Window();
};

std::ostream & operator<<(std::ostream & os, Window win);

#endif // WINDOW_HPP
