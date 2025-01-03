#include "adv_text_box.h"
#include "SDL_render.h"
#include "SDL_ttf.h"

#include <List>
#include <iostream>

AdvTextBox::AdvTextBox(InGameOverlayParameters *igop, TTF_Font *font, SDL_Color textColor)
    : m_text_color{textColor}, m_font{font}, m_igop{igop}
{

}

void AdvTextBox::Render(SDL_Renderer *renderer)
{
    if (m_dialogues.empty())
    {
        return;
    }
    switch (m_igop->m_block_shape) {
    case base_rectangle:
    {
        SDL_SetRenderDrawColor(renderer,255,128,0,200);
        SDL_Rect main_text_block = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y, m_igop->m_text_block_lenght, m_igop->m_text_block_height};
        SDL_RenderFillRect(renderer,&main_text_block);
        break;
    }
    case fading_rectangle:
    {
        break;
    }
    }
    int w,h;
    SDL_QueryTexture(m_dialogues.back().m_texture,NULL,NULL,&w,&h);
    SDL_Rect rect = {m_igop->m_text_block_position.m_x + 10, m_igop->m_text_block_position.m_y + 10, w, h};
    m_dialogues.back().m_rect = rect;
    SDL_RenderCopy(renderer,m_dialogues.back().m_texture,NULL,&m_dialogues.back().m_rect);
    SDL_Surface * char_name_surface;
    // std::cout << m_dialogues.back().m_talking->GetName() << std::endl;
    char_name_surface = TTF_RenderUTF8_Solid(m_font,m_dialogues.back().m_talking->GetName().c_str(),m_text_color);
    SDL_Texture * char_name_text = SDL_CreateTextureFromSurface(renderer,char_name_surface);
    SDL_QueryTexture(char_name_text,NULL,NULL,&w,&h);
    SDL_Rect char_name_rect = {m_igop->m_text_block_position.m_x, m_igop->m_text_block_position.m_y - (h+20),w + 20,h + 20};
    SDL_RenderFillRect(renderer,&char_name_rect);
    SDL_Rect rect_char = char_name_rect;
    rect_char.x += 5;
    rect_char.y += 5;
    rect_char.w -= 10;
    rect_char.h -= 10;
    SDL_RenderCopy(renderer,char_name_text,NULL,&rect_char);
    SDL_DestroyTexture(char_name_text);
    SDL_FreeSurface(char_name_surface);
}

void AdvTextBox::AddDialogueAtFront(const Dialogue &dial)
{
    m_dialogues.pop_back();
    m_dialogues.push_front(dial);
}

void AdvTextBox::AddDialogue(const Dialogue & dial)
{
    m_dialogues.clear();
    m_dialogues.push_back(dial);
}

void AdvTextBox::ClearDialogue()
{
    m_dialogues.clear();
}

void AdvTextBox::ReactEvent()
{

}
