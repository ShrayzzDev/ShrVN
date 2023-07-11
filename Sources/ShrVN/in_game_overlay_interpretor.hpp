#ifndef INGAMEOVERLAYINTERPRETOR_HPP
#define INGAMEOVERLAYINTERPRETOR_HPP

#include "IInGameOverlayInterpretor.h"

class InGameOverlayInterpretor : public IInGameOverlayInterpretor
{
public:
    InGameOverlayInterpretor();
    void SetTextMode(InGameOverlayParameters &igovparam, text_mode txt_mode) override;
    void SetInGameOptionPosition(InGameOverlayParameters &igovparam, in_game_option_position igoppos) override;
    void SetTextBlockShape(InGameOverlayParameters &igovparam, text_block_shape tbs) override;
    void SetTextBlockHeight(InGameOverlayParameters &igovparam, unsigned short height) override;
    void SetTextBlockLength(InGameOverlayParameters &igovparam, unsigned short length) override;
    void SetTextBlockOpacity(InGameOverlayParameters &igovparam, unsigned short opacity) override;
    void SetTextBlockXPosition(InGameOverlayParameters &igovparam, int xpos) override;
    void SetTextBlockYPosition(InGameOverlayParameters &igovparam, int ypos) override;
    void SetFontSize(InGameOverlayParameters &igovparam, unsigned short f_size) override;
};

#endif // INGAMEOVERLAYINTERPRETOR_HPP
