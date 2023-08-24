#include <filesystem>
#include <iostream>

#include "in_game_window.hpp"
#include "font.h"
#include "window.hpp"
#include "button.hpp"

InGameWindow::InGameWindow(ISaveLoader * isl, InGameOverlayParameters * igop, InGameMenuParameters * igmp)
    :m_igop{igop}, m_igmp{igmp}, m_sl{isl}
{

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
        throw std::invalid_argument("ERROR : Couldn't find the " + bg_img);
    }
    if (m_background_img != nullptr)
    {
        SDL_DestroyTexture(m_background_img);
    }
    m_background_img = IMG_LoadTexture(rend,full_path.generic_string().c_str());
    if (m_background_img == nullptr)
    {
        throw std::invalid_argument("ERROR : Couldn't open file " + bg_img);
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
    m_igop->m_text_mode = txt_mode;
}

void InGameWindow::SwitchTextMode()
{
    switch(m_igop->m_text_mode) {
    case ADV:
        m_igop->m_text_mode = NVL;
        break;

    case NVL:
        m_igop->m_text_mode = ADV;
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
    m_current_dialogue.clear();
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
    switch(m_igop->m_text_mode) {
    case ADV:
    {
        if (!IsMenuOpen)
        {
            if (IsTextShown)
            {
                if (m_current_dialogue.empty())
                {
                    break;
                }
                switch (m_igop->m_block_shape) {
                case base_rectangle:
                {
                    SDL_SetRenderDrawColor(rend,255,128,0,200);
                    SDL_Rect main_text_block = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y, m_igop->m_text_block_lenght, m_igop->m_text_block_height};
                    SDL_RenderFillRect(rend,&main_text_block);
                    break;
                }
                case fading_rectangle:
                {
                    break;
                }
                }
                int w,h;
                SDL_QueryTexture(m_current_dialogue.back().m_texture,NULL,NULL,&w,&h);
                SDL_Rect rect = {m_igop->m_text_block_position.m_x + 10, m_igop->m_text_block_position.m_y + 10, w, h};
                m_current_dialogue.back().m_rect = rect;
                SDL_RenderCopy(rend,m_current_dialogue.back().m_texture,NULL,&m_current_dialogue.back().m_rect);
                SDL_Surface * char_name_surface;
                char_name_surface = TTF_RenderText_Solid(m_font,m_current_dialogue.back().m_talking->GetName().c_str(),m_text_color);
                SDL_Texture * char_name_text = SDL_CreateTextureFromSurface(rend,char_name_surface);
                SDL_QueryTexture(char_name_text,NULL,NULL,&w,&h);
                SDL_Rect char_name_rect = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y - (h+20),w + 20,h + 20};
                SDL_RenderFillRect(rend,&char_name_rect);
                SDL_Rect rect_char = char_name_rect;
                rect_char.x += 5;
                rect_char.y += 5;
                rect_char.w -= 10;
                rect_char.h -= 10;
                SDL_RenderCopy(rend,char_name_text,NULL,&rect_char);
                SDL_DestroyTexture(char_name_text);
                SDL_FreeSurface(char_name_surface);
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
        break;
    }
    case NVL:
    {
        if ((IsTextShown && !IsMenuOpen) || IsMenuOpen)
        {
            SDL_SetRenderDrawColor(rend,0,0,0,190);
            SDL_Rect rect = {0,0,window_length,window_height};
            SDL_RenderFillRect(rend,&rect);
            if (IsMenuOpen)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                for (auto & btn : m_buttons)
                {
                    btn.RenderButton(rend,x,y,true);
                }
            }
        }
        if (!IsMenuOpen && IsTextShown)
        {
            unsigned short y_coord = 100;
            int w,h;
            for (auto & dial : m_current_dialogue)
            {
                SDL_Surface * name_surface;
                name_surface = TTF_RenderText_Solid_Wrapped(m_font,dial.m_talking->GetName().c_str(),m_text_color,300);
                SDL_Texture * name = SDL_CreateTextureFromSurface(rend,name_surface);
                SDL_QueryTexture(name,NULL,NULL,&w,&h);
                SDL_Rect rect_char_name = {(300-w)/3,y_coord,w,h};
                SDL_RenderCopy(rend,name,NULL,&rect_char_name);
                SDL_QueryTexture(dial.m_texture,NULL,NULL,&w,&h);
                SDL_Rect rect = {220, y_coord, w, h};
                dial.m_rect = rect;
                SDL_RenderCopy(rend,dial.m_texture,NULL,&dial.m_rect);
                y_coord += h + 20;
                SDL_DestroyTexture(name);
                SDL_FreeSurface(name_surface);
            }
        }
        break;
    }
    break;
    }
}

Dialogue InGameWindow::CreateDialogue(const std::string &text, Characters &chr, SDL_Renderer * rend)
{
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid_Wrapped(m_font,text.c_str(),m_text_color,m_igop->m_text_block_lenght);
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
    if (m_igop->m_text_mode == ADV && !m_current_dialogue.empty())
    {
        m_current_dialogue.pop_back();
    }
    m_current_dialogue.push_back(dial);
}

void InGameWindow::AddCurrentDialogueAtFront(const Dialogue &dial)
{
    if (m_igop->m_text_mode == ADV && !m_current_dialogue.empty())
    {
        m_current_dialogue.pop_back();
    }
    m_current_dialogue.push_front(dial);
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
    Sprite current = m_onscreen_sprites.at(image_path);
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
    std::cout << "'" << image_path << "'" << std::endl;
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

void InGameWindow::AddMovementToSprite(const std::string &image_path, Movement &mvt)
{
    if (!m_onscreen_sprites.contains(image_path))
    {
        throw std::invalid_argument("ERROR : image located at " + image_path + " isn't curretly used as an on screen sprite.");
    }
    m_onscreen_sprites.at(image_path).SetMovement(mvt,100);
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
