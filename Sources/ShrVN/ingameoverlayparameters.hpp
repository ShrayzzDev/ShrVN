#ifndef INGAMEOVERLAYPARAMETERS_H
#define INGAMEOVERLAYPARAMETERS_H

#include <fstream>

struct InGameOverlayParameters
{

};

void InitInGameOverlay(const std::ofstream & file);

InGameOverlayParameters ReadInGameOverlayParametersFile(const std::ofstream & file);

#endif // INGAMEOVERLAYPARAMETERS_H
