#ifndef INGAMEOVERLAYINTERPRETOR_HPP
#define INGAMEOVERLAYINTERPRETOR_HPP

#include "IInGameOverlayInterpretor.h"

class InGameOverlayInterpretor : public IInGameOverlayInterpretor
{
public:
    InGameOverlayInterpretor();
    void SetTextMode(InGameOverlayParameters &igovparam, text_mode txt_mode) const override;
    void SetInGameOptionPosition(InGameOverlayParameters &igovparam, in_game_option_position igoppos) const override;
    void SetTextBlockShape(InGameOverlayParameters &igovparam, text_block_shape tbs) const override;
    void SetTextBlockHeight(InGameOverlayParameters &igovparam, unsigned short height) const override;
    void SetTextBlockLength(InGameOverlayParameters &igovparam, unsigned short length) const override;
    void SetTextBlockOpacity(InGameOverlayParameters &igovparam, unsigned short opacity) const override;
    void SetTextBlockXPosition(InGameOverlayParameters &igovparam, int xpos) const override;
    void SetTextBlockYPosition(InGameOverlayParameters &igovparam, int ypos) const override;
    void SetFontSize(InGameOverlayParameters &igovparam, unsigned short f_size) const override;
    void SetFontType(InGameOverlayParameters &igovparam, const std::string &f_type) const override;
};

#endif // INGAMEOVERLAYINTERPRETOR_HPP
