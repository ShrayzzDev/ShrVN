#include <filesystem>
#include <iostream>

#include "window.hpp"
#include "initialisation_error.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Window::Window(const std::string & name, unsigned short height, unsigned short length, InGameOverlayParameters * igop, OptionsMenuParameters * omp, InGameMenuParameters * igmp, SavesMenuParameters * smp, MainMenuParameters * mmp)
    : m_name{name}, m_height{height}, m_length{length}, m_open{true}, m_igop{igop}, m_omp{omp}, m_igmp{igmp}, m_smp{smp}, m_mmp{mmp}, m_onscreen_sprites{}, IsClicked{false}
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
    if (TTF_Init() != 0)
    {
        std::string error = "ERROR : Couldn't initialize the text component: " + (std::string)SDL_GetError();
        throw Initialisation_Error(error.c_str());
    }
    SDL_SetRenderDrawBlendMode(m_renderer,SDL_BLENDMODE_BLEND);
    m_font = TTF_OpenFont("Laziness.ttf",m_igop->m_font_size);
    if (m_font == NULL)
    {
        std::cout << "je marche pas : " << SDL_GetError() << std::endl;
    }
    m_text_color = {0,0,0,255};
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

TTF_Font *Window::GetFont() const
{
    return m_font;
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
    if (m_background_img != nullptr)
    {
        SDL_DestroyTexture(m_background_img);
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

void Window::SetCurrentScreen(CurrentScreen current)
{
    m_current = current;
}

void Window::SwitchTextMode()
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

void Window::AddCurrentDialogue(Dialogue &dial)
{
    if (m_igop->m_text_mode == ADV && !m_current_dialogue.empty())
    {
        m_current_dialogue.pop_back();
    }
    m_current_dialogue.push_back(dial);
    m_previous_dialogue.push_back(dial);
    if (m_previous_dialogue.size() >= 10)
    {
        SDL_DestroyTexture(m_previous_dialogue.front().m_text);
        m_previous_dialogue.pop_front();
    }
}

void Window::CleanCurrentMessages()
{
    m_current_dialogue.clear();
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
                IsClicked = true;
                for (auto & sprt : m_onscreen_sprites)
                {
                    if (!sprt.second.IsMovementEmpty())
                    {
                        sprt.second.SetPosToLastMovement();
                        sprt.second.ClearMovement();
                    }
                }
                break;
            }
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
    for (auto & dial : m_previous_dialogue)
    {
        SDL_DestroyTexture(dial.m_text);
    }
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
    SDL_RenderCopy(m_renderer,m_background_img,NULL,NULL);
    switch (m_current) {
    case InGame:
    {
        for (auto & sprite : m_onscreen_sprites)
        {
            if (sprite.second.RenderSprite(m_renderer))
            {
                std::cerr << "Error while rendering image : " << SDL_GetError() << std::endl;
            }
        }
        switch(m_igop->m_text_mode) {
        case ADV:
        {
            if (m_current_dialogue.empty())
            {
                break;
            }
            switch (m_igop->m_block_shape) {
            case base_rectangle:
            {
                SDL_SetRenderDrawColor(m_renderer,255,128,0,200);
                SDL_Rect main_text_block = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y, m_igop->m_text_block_lenght, m_igop->m_text_block_height};
                SDL_RenderFillRect(m_renderer,&main_text_block);
                break;
            }
            case fading_rectangle:
            {
                break;
            }
            }
            int w,h;
            SDL_QueryTexture(m_current_dialogue.back().m_text,NULL,NULL,&w,&h);
            SDL_Rect rect = {m_igop->m_text_block_position.m_x + 10, m_igop->m_text_block_position.m_y + 10, w, h};
            m_current_dialogue.back().m_rect = rect;
            SDL_RenderCopy(m_renderer,m_current_dialogue.back().m_text,NULL,&m_current_dialogue.back().m_rect);
            SDL_Surface * char_name_surface;
            char_name_surface = TTF_RenderText_Solid(m_font,m_current_dialogue.back().m_talking->GetName().c_str(),m_text_color);
            SDL_Texture * char_name_text = SDL_CreateTextureFromSurface(m_renderer,char_name_surface);
            SDL_QueryTexture(char_name_text,NULL,NULL,&w,&h);
            SDL_Rect char_name_rect = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y - (h+20),w + 20,h + 20};
            SDL_RenderFillRect(m_renderer,&char_name_rect);
            SDL_Rect rect_char = char_name_rect;
            rect_char.x += 5;
            rect_char.y += 5;
            rect_char.w -= 10;
            rect_char.h -= 10;
            SDL_RenderCopy(m_renderer,char_name_text,NULL,&rect_char);
            SDL_DestroyTexture(char_name_text);
            SDL_FreeSurface(char_name_surface);
            break;
        }
        case NVL:
        {
            SDL_SetRenderDrawColor(m_renderer,0,0,0,190);
            SDL_Rect rect = {0,0,m_length,m_height};
            SDL_RenderFillRect(m_renderer,&rect);
            unsigned short y_coord = 100;
            int w,h;
            for (auto & dial : m_current_dialogue)
            {
                SDL_Surface * name_surface;
                name_surface = TTF_RenderText_Solid_Wrapped(m_font,dial.m_talking->GetName().c_str(),m_text_color,300);
                SDL_Texture * name = SDL_CreateTextureFromSurface(m_renderer,name_surface);
                SDL_QueryTexture(name,NULL,NULL,&w,&h);
                SDL_Rect rect_char_name = {(300-w)/3,y_coord,w,h};
                SDL_RenderCopy(m_renderer,name,NULL,&rect_char_name);
                SDL_QueryTexture(dial.m_text,NULL,NULL,&w,&h);
                SDL_Rect rect = {220, y_coord, w, h};
                dial.m_rect = rect;
                SDL_RenderCopy(m_renderer,dial.m_text,NULL,&dial.m_rect);
                y_coord += h + 20;
                SDL_DestroyTexture(name);
                SDL_FreeSurface(name_surface);
            }
            break;
        }
        }
        break;
    }
    }
    SDL_RenderPresent(m_renderer);
}

Dialogue Window::CreateDialogue(const std::string &text, Characters &chr)
{
    SDL_Surface * text_surface;
    text_surface = TTF_RenderText_Solid_Wrapped(m_font,text.c_str(),m_text_color,m_igop->m_text_block_lenght);
    SDL_Texture * text_texture = SDL_CreateTextureFromSurface(m_renderer,text_surface);
    return {text_texture,&chr};
}

std::ostream & operator<<(std::ostream & os, Window win)
{
    return os << "Name: " << win.GetName() << std::endl
              << "Height" << win.GetHeight() << std::endl
              << "Length" << win.GetLength() << std::endl;
}
