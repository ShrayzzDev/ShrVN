#ifndef IINGAMEOVERLAYINTERPRETOR_
#define IINGAMEOVERLAYINTERPRETOR_

#include "in_game_overlay_parameters.hpp"
#include "text_mode.h"
#include "in_game_options_position.h"
#include "text_block_shape.h"

class IInGameOverlayInterpretor
{
public:
    virtual void SetTextMode(InGameOverlayParameters & igovparam, text_mode txt_mode) = 0;
    virtual void SetInGameOptionPosition(InGameOverlayParameters & igovparam, in_game_option_position igoppos) = 0;
    virtual void SetTextBlockShape(InGameOverlayParameters & igovparam, text_block_shape tbs) = 0;
    virtual void SetTextBlockHeight(InGameOverlayParameters & igovparam, unsigned short height) = 0;
    virtual void SetTextBlockLength(InGameOverlayParameters & igovparam, unsigned short length) = 0;
    virtual void SetTextBlockOpacity(InGameOverlayParameters & igovparam, unsigned short opacity) = 0;
    virtual void SetTextBlockXPosition(InGameOverlayParameters & igovparam, int xpos) = 0;
    virtual void SetTextBlockYPosition(InGameOverlayParameters & igovparam, int ypos) = 0;
    virtual void SetFontSize(InGameOverlayParameters & igovparam, unsigned short f_size) = 0;
};

#endif // IINGAMEOVERLAYINTERPRETOR_
