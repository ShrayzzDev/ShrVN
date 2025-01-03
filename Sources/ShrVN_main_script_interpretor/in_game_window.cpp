#include <filesystem>
#include <iostream>

#include "in_game_window.hpp"
#include "font.h"
#include "window.hpp"
#include "button.hpp"
#include "adv_text_box.h"
#include "nvl_text_box.h"

InGameWindow::InGameWindow()
{
}

InGameWindow::InGameWindow(ISaveLoader * isl, InGameOverlayParameters * igop, InGameMenuParameters * igmp)
    :m_igop{igop}, m_igmp{igmp}, m_sl{isl}
{
    SetTextMode(igop->m_text_mode);
}

InGameOverlayParameters *InGameWindow::GetIgop() const
{
    return m_igop;
}

SDL_Texture *InGameWindow::GetBgImg() const
{
    return m_background_img;
}

void InGameWindow::SetBackgroundImg(const std::string &bg_img, SDL_Renderer * rend)
{
    std::filesystem::path full_path = std::filesystem::current_path().generic_string() + "/images/" + bg_img;
    if (! std::filesystem::exists(full_path))
    {
        std::string mess = "ERROR : Couldn't find the \'" + bg_img + "'";
        throw std::invalid_argument(mess);
    }
    if (m_background_img != nullptr)
    {
        SDL_DestroyTexture(m_background_img);
    }
    m_background_img = IMG_LoadTexture(rend,full_path.generic_string().c_str());
    if (m_background_img == nullptr)
    {
        throw std::invalid_argument("ERROR : Couldn't open background file while setting it" + bg_img);
    }
}

void InGameWindow::SetTextColor(SDL_Color &color)
{
    m_text_color = color;
}

void InGameWindow::SetFont()
{
    m_font = CreateFont(m_igop->m_font_type,m_igop->m_font_size);
    if (m_font == NULL)
    {
        std::cerr << "Couldn't find the font " << m_igop->m_font_type << " for InGame" << std::endl;
    }
}

void InGameWindow::SetCurrentScript(std::ifstream * file)
{
    m_script = file;
}

void InGameWindow::SetTextMode(text_mode txt_mode)
{
    if (m_igop != nullptr) m_igop->m_text_mode = txt_mode;
    if (m_textDisplayer != nullptr) free(m_textDisplayer);
    switch (txt_mode)
    {
        case ADV:
            m_textDisplayer = new AdvTextBox(m_igop, m_font, m_text_color);
            break;

        case NVL:
            m_textDisplayer = new NvlTextBox(m_igop, m_font, m_text_color);
            break;
    }
}

void InGameWindow::SwitchTextMode()
{
    switch(m_igop->m_text_mode) {
    case ADV:
        SetTextMode(NVL);
        break;

    case NVL:
        SetTextMode(ADV);
        break;
    }
}

void InGameWindow::ShowText()
{
    IsMenuOpen = false;
    IsTextShown = true;
}

const Sprite * InGameWindow::GetSprite(const std::string &img_path) const
{
    return &m_onscreen_sprites.at(img_path);
}

const std::string &InGameWindow::GetFontType() const
{
    return m_igop->m_font_type;
}

unsigned short InGameWindow::GetFontSize() const
{
    return m_igop->m_font_size;
}

text_mode InGameWindow::GetTextMode() const
{
    return m_igop->m_text_mode;
}

TTF_Font * InGameWindow::GetFont() const
{
    return m_font;
}

std::ifstream * InGameWindow::GetCurrentScript()
{
    return m_script;
}

const std::list<Dialogue> & InGameWindow::GetPreviousDialogue() const
{
    return m_previous_dialogue;
}

void InGameWindow::CleanCurrentMessages()
{
    m_textDisplayer->ClearDialogue();
}

void InGameWindow::CleanPreviousDialogue()
{
    m_previous_dialogue.clear();
}

void InGameWindow::CleanOnScreenSprites()
{
    for (auto & sprt : m_onscreen_sprites)
    {
        SDL_DestroyTexture(sprt.second.GetTexture());
    }
    m_onscreen_sprites.clear();
}

void InGameWindow::ReactEvent(Window * win, SDL_Event & event)
{
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        switch (event.button.clicks) {
        case SDL_BUTTON_LEFT:
            Click(win);
            break;
        }
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
        case SDLK_RETURN:
            Click(win);
            break;
        case SDLK_ESCAPE:
            win->TakeScreenShot();
            if (!IsMenuOpen)
            {
                IsTextShown = false;
            }
            else
            {
                IsTextShown = true;
            }
            IsMenuOpen = !IsMenuOpen;
            break;
        case SDLK_F1:
            IsTextShown = !IsTextShown;
            break;
        case SDLK_LEFT:
            if (IsMenuOpen)
            {
                if (m_btn_choice_count == -1)
                {
                    m_btn_choice_count = 0;
                }
                else if (m_btn_choice_count > 0)
                {
                    m_btn_choice_count--;
                }
                Point pt = m_buttons[m_btn_choice_count].GetMiddle();
                SDL_WarpMouseInWindow(NULL,pt.m_x,pt.m_y);
            }
            break;
        case SDLK_RIGHT:
            if (IsMenuOpen)
            {
                if (m_btn_choice_count == -1)
                {
                    m_btn_choice_count = 0;
                }
                else if (m_btn_choice_count < 1)
                {
                    m_btn_choice_count++;
                }
                Point pt = m_buttons[m_btn_choice_count].GetMiddle();
                SDL_WarpMouseInWindow(NULL,pt.m_x,pt.m_y);
            }
        }
        break;
    }
}

void InGameWindow::RenderWindow(SDL_Renderer *rend, unsigned short window_length, unsigned short window_height)
{
    SDL_RenderCopy(rend,m_background_img,NULL,NULL);
    for (auto & sprite : m_onscreen_sprites)
    {
        if (sprite.second.RenderSprite(rend))
        {
            std::cerr << "Error while rendering image : " << SDL_GetError() << std::endl;
        }
    }
    if (!IsMenuOpen)
    {
        if (IsTextShown)
        {
            m_textDisplayer->Render(rend);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(rend,0,0,0,190);
        SDL_Rect rect = {0,0,window_length,window_height};
        SDL_RenderFillRect(rend,&rect);
        int x,y;
        SDL_GetMouseState(&x,&y);
        for (auto & btn : m_buttons)
        {
            btn.RenderButton(rend,x,y,true);
        }
    }
}

Dialogue InGameWindow::CreateDialogue(const std::string &text, Characters &chr, SDL_Renderer * rend)
{
    SDL_Surface * text_surface;
    text_surface = TTF_RenderUTF8_Solid_Wrapped(m_font,text.c_str(),m_text_color,m_igop->m_text_block_lenght);
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(rend,text_surface);
    return {text_texture,text,&chr,{0,0,0,0}};
}

void InGameWindow::InitButtons(SDL_Renderer * rend)
{
    short base_x = 200, base_y = 300;
    SDL_Rect rect = {base_x,base_y,m_igmp->m_button_length,m_igmp->m_button_height};
    Button settings = {"Setting","settings.png",rect,rend};
    settings.m_WhenPressed = SettingButton;
    m_buttons.push_back(settings);
    base_x += m_igmp->m_button_length + 20;
    rect = {base_x,base_y,m_igmp->m_button_length,m_igmp->m_button_height};
    Button save = {"Save","save.png",rect,rend};
    save.m_WhenPressed = SaveButton;
    m_buttons.push_back(save);
    base_x += m_igmp->m_button_length + 20;
    rect = {base_x,base_y,m_igmp->m_button_length,m_igmp->m_button_height};
    Button load = {"Load","save.png",rect,rend};
    load.m_WhenPressed = LoadButton;
    m_buttons.push_back(load);
}

void InGameWindow::AddCurrentDialogue(const Dialogue & dial)
{
    m_textDisplayer->AddDialogue(dial);
}

void InGameWindow::AddCurrentDialogueAtFront(const Dialogue &dial)
{
    m_textDisplayer->AddDialogueAtFront(dial);
}

void InGameWindow::AddPreviousDialogue(const Dialogue & dial)
{
    m_previous_dialogue.push_back(dial);
    if (m_previous_dialogue.size() >= 100)
    {
        SDL_DestroyTexture(m_previous_dialogue.front().m_texture);
        m_previous_dialogue.pop_front();
    }
}

void InGameWindow::RemoveOnScreenSprite(const std::string &image_path)
{
    if (!m_onscreen_sprites.contains(image_path))
    {
        throw std::invalid_argument("ERROR : image located at " + image_path + " isn't curretly used as an on screen sprite.");
    }
    Sprite & current = m_onscreen_sprites.at(image_path);
    current.ClearMovement();
    SDL_DestroyTexture(current.GetTexture());
    m_onscreen_sprites.erase(image_path);
}

void InGameWindow::DestroyOnScreenSprite()
{
    for (auto & sprite : m_onscreen_sprites)
    {
        SDL_DestroyTexture(sprite.second.GetTexture());
    }
}

void InGameWindow::DestroyDialogues()
{
    for (auto & dial : m_previous_dialogue)
    {
        SDL_DestroyTexture(dial.m_texture);
    }
}

void InGameWindow::AddOnScreenSprite(const std::string &image_path, Point coord, SDL_Renderer * rend, SDL_Texture *texture)
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
        SDL_Texture * new_texture = IMG_LoadTexture(rend,full_path.generic_string().c_str());
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
    Sprite current_sprite = Sprite(rect,texture);
    m_onscreen_sprites.insert(std::pair(image_path,current_sprite));
}

void InGameWindow::Click(Window * win)
{
    if (!IsMenuOpen)
    {
        win->IsClicked = true;
    }
    else
    {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x,&mouse_y);
        for (auto btn : m_buttons)
        {
            if (btn.IsWithinBound(mouse_x,mouse_y))
            {
                btn.m_WhenPressed(win,this);
            }
        }
    }
    if (!IsTextShown)
    {
        IsTextShown = true;
    }
    for (auto & sprt : m_onscreen_sprites)
    {
        if (!sprt.second.IsMovementEmpty())
        {
            sprt.second.SetPosToLastMovement();
            sprt.second.ClearMovement();
        }
    }
}

void InGameWindow::AddMovementToSprite(const std::string &image_path, Movement &mvt, SDL_Renderer * rend)
{
    if (!m_onscreen_sprites.contains(image_path))
    {
        throw std::invalid_argument("ERROR : image located at " + image_path + " isn't curretly used as an on screen sprite.");
    }
    m_onscreen_sprites.at(image_path).SetMovement(mvt, 100, rend);
}

void SettingButton(Window * win, CurrentScreen * cs)
{
    std::cout << "je suis les paramètres" << std::endl;
}

void SaveButton(Window * win, CurrentScreen * cs)
{  
    win->SetCurrentScreen(save);
}

void LoadButton(Window * win, CurrentScreen * cs)
{
    win->SetCurrentScreen(load);
}
