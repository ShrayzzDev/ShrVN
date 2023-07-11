#ifndef IN_GAME_OVERLAY_PARAMETERS_H
#define IN_GAME_OVERLAY_PARAMETERS_H

#include <fstream>

#include "text_mode.h"
#include "in_game_options_position.h"
#include "text_block_shape.h"
#include "point.hpp"

struct InGameOverlayParameters
{
    text_mode m_text_mode = ADV;
    in_game_option_position m_option_position = outside_right;
    text_block_shape m_block_shape = base_rectangle;
    unsigned short m_text_block_height = 250;
    unsigned short m_text_block_lenght = 750;
    unsigned short m_text_block_opacity = 80;
    Point m_text_block_position;
    unsigned short m_font_size = 17;
};

// Use the file given in parameter and write base parameters.
void InitInGameOverlay(std::ofstream & file);

std::ostream & operator<<(std::ostream & os, InGameOverlayParameters & Parameters);

#endif // IN_GAME_OVERLAY_PARAMETERS_H
