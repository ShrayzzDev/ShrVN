#include "in_game_overlay_interpretor.hpp"

InGameOverlayInterpretor::InGameOverlayInterpretor()
{

}

void InGameOverlayInterpretor::SetTextMode(InGameOverlayParameters &igovparam, text_mode txt_mode) const
{
    igovparam.m_text_mode = txt_mode;
}

void InGameOverlayInterpretor::SetInGameOptionPosition(InGameOverlayParameters &igovparam, in_game_option_position igoppos) const
{
    igovparam.m_option_position = igoppos;
}

void InGameOverlayInterpretor::SetTextBlockShape(InGameOverlayParameters &igovparam, text_block_shape tbs) const
{
    igovparam.m_block_shape = tbs;
}

void InGameOverlayInterpretor::SetTextBlockHeight(InGameOverlayParameters &igovparam, unsigned short height) const
{
    igovparam.m_text_block_height = height;
}

void InGameOverlayInterpretor::SetTextBlockLength(InGameOverlayParameters &igovparam, unsigned short length) const
{
    igovparam.m_text_block_lenght = length;
}

void InGameOverlayInterpretor::SetTextBlockOpacity(InGameOverlayParameters &igovparam, unsigned short opacity) const
{
    igovparam.m_text_block_opacity = opacity;
}

void InGameOverlayInterpretor::SetTextBlockXPosition(InGameOverlayParameters &igovparam, int xpos) const
{
    igovparam.m_text_block_position.m_x = xpos;
}

void InGameOverlayInterpretor::SetTextBlockYPosition(InGameOverlayParameters &igovparam, int ypos) const
{
    igovparam.m_text_block_position.m_y = ypos;
}

void InGameOverlayInterpretor::SetFontSize(InGameOverlayParameters &igovparam, unsigned short f_size) const
{
    igovparam.m_font_size = f_size;
}
