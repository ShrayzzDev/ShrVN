#ifndef SAVE_BUTTON_H
#define SAVE_BUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

class Save;

class Window;

class CurrentScreen;

namespace button
{
    class SaveButton
    {
        SDL_Texture * m_preview;
        SDL_Texture * m_last_char_name;
        SDL_Texture * m_last_dialogue;
        SDL_Rect m_rect;
        Save * m_save;
        TTF_Font * m_no_save_font;
        TTF_Font * m_char_name_font;
        TTF_Font * m_dial_font;
    public:
        SaveButton(SDL_Rect rect);
        void (*m_WhenPressed)(Window*,CurrentScreen*) = nullptr;
        void RenderBtn(SDL_Renderer * rend, short mouse_x, short mouse_y);
        bool IsWithinBound(short mouse_x, short mouse_y);
        void SetSave(Save * save, SDL_Renderer * rend);
        void LoadImage(short save_slot, short save_page, Window * win);
    };
}

#endif // SAVE_BUTTON_H
