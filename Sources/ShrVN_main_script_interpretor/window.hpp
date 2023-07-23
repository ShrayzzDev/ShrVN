#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>

#include <string>
#include <ostream>
#include <map>

#include "in_game_overlay_parameters.hpp"
#include "options_menu_parameters.hpp"
#include "in_game_menu_parameters.hpp"
#include "saves_menu_parameters.hpp"
#include "main_menu_parameters.hpp"
#include "point.hpp"
#include "sprite.hpp"

class Window
{
    std::string m_name;
    unsigned short m_height;
    unsigned short m_length;
    bool m_open;
    InGameOverlayParameters * m_igop;
    OptionsMenuParameters * m_omp;
    InGameMenuParameters * m_igmp;
    SavesMenuParameters * m_smp;
    MainMenuParameters * m_mmp;
    SDL_Texture * m_background_img;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::map<std::string,Sprite> m_onscreen_sprites;
public:
    Window(const std::string & name, unsigned short height = 1080, unsigned short length = 1920, InGameOverlayParameters * igop = nullptr, OptionsMenuParameters * omp = nullptr, InGameMenuParameters * igmp = nullptr, SavesMenuParameters * smp = nullptr, MainMenuParameters * mmp = nullptr);
    void Init();
    const std::string & GetName() const;
    unsigned short GetHeight() const;
    unsigned short GetLength() const;
    SDL_Renderer * GetRenderer() const;
    Sprite * GetSprite(const std::string & img_path);
    void SetBackgroundImg(const std::string & bg_img);
    void SetInGameOverlayParameters(InGameOverlayParameters * igop);
    void SetOptionsMenuParameters(OptionsMenuParameters * omp);
    void SetInGameMenuParameters(InGameMenuParameters * igmp);
    void SetSavesMenuParameters(SavesMenuParameters * smp);
    void SetMainMenuParameters(MainMenuParameters * mmp);
    void AddOnScreenSprite(const std::string & image_path, Point coord = {0,0}, SDL_Texture * texture = nullptr);
    void ReactEvent();
    bool IsOpen();
    void RenderImage();
    ~Window();
};

std::ostream & operator<<(std::ostream & os, Window win);

#endif // WINDOW_HPP
