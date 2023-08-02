#ifndef INGAMEWINDOW_HPP
#define INGAMEWINDOW_HPP

#include <SDL.h>
#include <map>
#include <string>
#include <SDL_ttf.h>

#include "in_game_overlay_parameters.hpp"
#include "sprite.hpp"
#include "dialogue.h"

class InGameWindow
{
    SDL_Texture * m_background_img = nullptr;
    SDL_Color m_text_color;
    TTF_Font * m_font = nullptr;
    InGameOverlayParameters * m_igop;
    std::map<std::string,Sprite> m_onscreen_sprites;
    std::list<Dialogue> m_previous_dialogue;
    std::list<Dialogue> m_current_dialogue;
public:
    InGameWindow(InGameOverlayParameters * igop = nullptr);
    InGameOverlayParameters * GetIgop() const;
    SDL_Texture * GetBgImg() const;
    const Sprite * GetSprite(const std::string &img_path) const;
    const std::string & GetFontType() const;
    unsigned short GetFontSize() const;
    text_mode GetTextMode() const;
    TTF_Font * GetFont() const;
    void SetBackgroundImg(const std::string & bg_img, SDL_Renderer * rend);
    void SetTextColor(SDL_Color & color);
    void SetFont();
    void SetTextMode(text_mode txt_mode);
    void SwitchTextMode();
    void AddCurrentDialogue(Dialogue &dial);
    void AddOnScreenSprite(const std::string &image_path, Point coord, SDL_Renderer * rend, SDL_Texture *texture = nullptr);
    void AddMovementToSprite(const std::string &image_path, Movement &mvt);
    void RemoveOnScreenSprite(const std::string &image_path);
    Dialogue CreateDialogue(const std::string &text, Characters &chr, SDL_Renderer * rend);
    void DestroyOnScreenSprite();
    void DestroyDialogues();
    void CleanCurrentMessages();
    void Click();
    void RenderWindow(SDL_Renderer * rend, unsigned short window_length, unsigned short window_height);
};

#endif // INGAMEWINDOW_HPP
