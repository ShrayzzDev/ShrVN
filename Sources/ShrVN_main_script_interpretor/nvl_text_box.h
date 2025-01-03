#ifndef NVLTEXTBOX_H
#define NVLTEXTBOX_H

#include "SDL_ttf.h"
#include "itextdisplayer.h"
#include "observableobject.h"
#include "in_game_overlay_parameters.hpp"



class NvlTextBox : public ObservableObject, public ITextDisplayer
{
    SDL_Color m_text_color;
    TTF_Font *m_font;
    InGameOverlayParameters *m_igop;
public:
    NvlTextBox(InGameOverlayParameters *igop, TTF_Font *font, SDL_Color textColor);

    // ITextDisplayer interface
public:
    void AddDialogue(const Dialogue & dial) override;
    void ClearDialogue() override;
    void Render(SDL_Renderer *renderer) override;

    // ObservableObject interface
public:
    void ReactEvent() override;

    // ITextDisplayer interface
public:
    void AddDialogueAtFront(const Dialogue &dial) override;
};

#endif // NVLTEXTBOX_H
