#ifndef INGAMEWINDOW_HPP
#define INGAMEWINDOW_HPP

#include <SDL.h>
#include <map>
#include <string>
#include <SDL_ttf.h>
#include <vector>

#include "in_game_overlay_parameters.hpp"
#include "in_game_menu_parameters.hpp"
#include "ISaveLoader.hpp"
#include "CurrentScreen.h"
#include "dialogue.h"
#include "sprite.hpp"
#include "button.hpp"

class Window;

class InGameWindow : public CurrentScreen
{
    SDL_Texture * m_background_img = nullptr;
    SDL_Color m_text_color;
    TTF_Font * m_font = nullptr;
    InGameOverlayParameters * m_igop;
    InGameMenuParameters * m_igmp;
    bool IsMenuOpen = false;
    bool IsTextShown = true;
    std::ifstream * m_script;
    std::map<std::string,Sprite> m_onscreen_sprites;
    std::list<Dialogue> m_previous_dialogue;
    std::list<Dialogue> m_current_dialogue;
    std::vector<Button> m_buttons;
    short m_btn_choice_count = -1;
public:
    ISaveLoader * m_sl;
    InGameWindow(ISaveLoader * isl = nullptr, InGameOverlayParameters * igop = nullptr, InGameMenuParameters * igmp = nullptr);
    InGameOverlayParameters * GetIgop() const;
    SDL_Texture * GetBgImg() const;
    const Sprite * GetSprite(const std::string &img_path) const;
    const std::string & GetFontType() const;
    unsigned short GetFontSize() const;
    text_mode GetTextMode() const;
    TTF_Font * GetFont() const;
    std::ifstream * GetCurrentScript();
    const std::list<Dialogue> & GetPreviousDialogue() const;
    void SetBackgroundImg(const std::string & bg_img, SDL_Renderer * rend);
    void SetTextColor(SDL_Color & color);
    void SetFont();
    void SetCurrentScript(std::ifstream * file);
    void SetTextMode(text_mode txt_mode);
    void SwitchTextMode();
    void AddPreviousDialogue(const Dialogue & dial);
    void AddCurrentDialogue(const Dialogue & dial);
    void AddOnScreenSprite(const std::string &image_path, Point coord, SDL_Renderer * rend, SDL_Texture *texture = nullptr);
    void AddMovementToSprite(const std::string &image_path, Movement &mvt);
    void RemoveOnScreenSprite(const std::string &image_path);
    Dialogue CreateDialogue(const std::string &text, Characters &chr, SDL_Renderer * rend);
    void InitButtons(SDL_Renderer * rend);
    void DestroyOnScreenSprite();
    void DestroyDialogues();
    void CleanCurrentMessages();
    void ReactEvent(Window * win, SDL_Event & event) override;
    void Click(Window * win);
    void RenderWindow(SDL_Renderer * rend, unsigned short window_length, unsigned short window_height) override;
};

void SettingButton(Window * win, CurrentScreen * cs);
void SaveButton(Window * win, CurrentScreen * cs);
void LoadButton(Window * win, CurrentScreen * cs);

#endif // INGAMEWINDOW_HPP
