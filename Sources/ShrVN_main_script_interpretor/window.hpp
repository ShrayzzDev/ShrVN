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
#include "CurrentScreenEnum.h"
#include "in_game_window.hpp"
#include "CurrentScreen.h"
#include "save_screen.h"
#include "sprite.hpp"

class Window
{
    std::string m_name;
    unsigned short m_height;
    unsigned short m_length;
    bool m_open;
    std::map<std::string,Characters> * m_char_map;
    CurrentScreen * m_current;
    InGameWindow m_igw;
    SaveScreen m_sw;
    OptionsMenuParameters * m_omp;
    MainMenuParameters * m_mmp;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
public:
    Window(const std::string & name, unsigned short height = 1080, unsigned short length = 1920, ISaveLoader * isl = nullptr, InGameOverlayParameters * igop = nullptr, OptionsMenuParameters * omp = nullptr, InGameMenuParameters * igmp = nullptr, SavesMenuParameters * smp = nullptr, MainMenuParameters * mmp = nullptr, std::map<std::string,Characters> * char_map = nullptr);
    void Init(std::ifstream & script);
    const std::string & GetName() const;
    unsigned short GetHeight() const;
    unsigned short GetLength() const;
    SDL_Renderer * GetRenderer() const;
    TTF_Font * GetFont() const;
    Sprite * GetSprite(const std::string & img_path);
    std::map<std::string,Characters> * GetCharMap();
    InGameWindow & GetIgw();
    SaveScreen & GetSc();
    void SetInGame(ISaveLoader * isl, InGameOverlayParameters * igop, InGameMenuParameters * igmp);
    void SetSaveScreen(SavesMenuParameters * smp);
    void SetOptionsMenuParameters(OptionsMenuParameters * omp);
    void SetMainMenuParameters(MainMenuParameters * mmp);
    void SetCurrentScreen(CurrentScreenEnum cs);
    void AddSpriteToBuffer(const std::string & img_path, Point coord);
    void Maximize();
    void UpdateSave(int nb_line,const Dialogue & dial);
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
