#ifndef ADV_TEXT_BOX_H
#define ADV_TEXT_BOX_H


#include "SDL_render.h"
#include "SDL_ttf.h"
#include "in_game_overlay_parameters.hpp"
#include "itextdisplayer.h"
#include "observableobject.h"
#include "dialogue.h"

class AdvTextBox : public ObservableObject, public ITextDisplayer
{
    SDL_Color m_text_color;
    TTF_Font *m_font;
    InGameOverlayParameters *m_igop;
public:
    AdvTextBox(InGameOverlayParameters *igop, TTF_Font *font, SDL_Color textColor);

    // ObservableObject interface
public:
    void ReactEvent() override;

    // ITextDisplayer interface
public:
    void AddDialogue(const Dialogue & dial) override;
    void ClearDialogue() override;
    void Render(SDL_Renderer *renderer) override;

    // ITextDisplayer interface
public:
    void AddDialogueAtFront(const Dialogue &dial) override;
};

#endif // ADV_TEXT_BOX_H
