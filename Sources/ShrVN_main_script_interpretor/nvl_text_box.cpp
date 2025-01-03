#include "nvl_text_box.h"

NvlTextBox::NvlTextBox(InGameOverlayParameters *igop, TTF_Font *font, SDL_Color textColor)
    : m_text_color{textColor}, m_font{font}, m_igop{igop}
{

}

void NvlTextBox::AddDialogue(const Dialogue & dial)
{
    m_dialogues.push_back(dial);
}

void NvlTextBox::ClearDialogue()
{
    m_dialogues.clear();
}

void NvlTextBox::Render(SDL_Renderer *renderer)
{
    unsigned short y_coord = 100;
    int w,h;
    for (auto & dial : m_dialogues)
    {
        SDL_Surface * name_surface;
        name_surface = TTF_RenderUTF8_Solid_Wrapped(m_font,dial.m_talking->GetName().c_str(),m_text_color,300);
        SDL_Texture * name = SDL_CreateTextureFromSurface(renderer,name_surface);
        SDL_QueryTexture(name,NULL,NULL,&w,&h);
        SDL_Rect rect_char_name = {(300-w)/3,y_coord,w,h};
        SDL_RenderCopy(renderer,name,NULL,&rect_char_name);
        SDL_QueryTexture(dial.m_texture,NULL,NULL,&w,&h);
        SDL_Rect rect = {220, y_coord, w, h};
        dial.m_rect = rect;
        SDL_RenderCopy(renderer,dial.m_texture,NULL,&dial.m_rect);
        y_coord += h + 20;
        SDL_DestroyTexture(name);
        SDL_FreeSurface(name_surface);
    }
}

void NvlTextBox::ReactEvent()
{

}

void NvlTextBox::AddDialogueAtFront(const Dialogue &dial)
{
    m_dialogues.push_front(dial);
}
