#ifndef INGAMEOVERLAYPARSERER_HPP
#define INGAMEOVERLAYPARSERER_HPP

#include <fstream>

#include "IInGameOverlayInterpretor.h"

class InGameOverlayParserer
{
    IInGameOverlayInterpretor * m_interpretor;
public:
    InGameOverlayParserer(IInGameOverlayInterpretor * interpretor);
    InGameOverlayParameters * ReadInGameOverlayParametersFile(std::ifstream & file);
};

#endif // INGAMEOVERLAYPARSERER_HPP
