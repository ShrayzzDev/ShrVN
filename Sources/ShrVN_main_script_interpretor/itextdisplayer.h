#ifndef ITEXTDISPLAYER_H
#define ITEXTDISPLAYER_H

#include "dialogue.h"

#include <list>

class ITextDisplayer
{
protected:
    std::list<Dialogue> m_dialogues;
public:
    void virtual AddDialogue(const Dialogue & dial) = 0;
    void virtual AddDialogueAtFront(const Dialogue & dial) = 0;
    void virtual ClearDialogue() = 0;
    void virtual Render(SDL_Renderer *renderer) = 0;
};

#endif // ITEXTDISPLAYER_H
