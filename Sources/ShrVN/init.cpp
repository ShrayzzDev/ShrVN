#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "init.h"
#include "ingamemenuparameters.hpp"
#include "ingameoverlayparameters.hpp"
#include "menuparameters.hpp"
#include "optionsmenuparameters.hpp"
#include "savesmenuparameters.hpp"

using namespace std;

void CreateEmptyProject(const string & project_path, const string & project_name)
{
    string full_project_path = project_path + "/" + project_name;
    if (filesystem::exists(full_project_path))
    {
        throw filesystem::filesystem_error("ERROR : the directory " + project_name + " already exists.",error_code());
    }
    filesystem::create_directory(full_project_path);
    filesystem::create_directory(full_project_path + "/music");
    filesystem::create_directory(full_project_path + "/image");
    filesystem::create_directory(full_project_path + "/init");
    filesystem::path old_path = filesystem::current_path();
    filesystem::current_path(full_project_path);
    ofstream CharFile("Characters.shrvn");
    CharFile.close();
    filesystem::current_path("/init");
    ofstream InGameMenuFile("InGameMenu.shvrn"), InGameOverlayFile("InGameOverlay.shrvn"), MenuFile("Menu.shrvn"), OptionsFile("OptionsMenu.shrvn"), SavesFile("SavesMenu.shrvn");
    InitInGameMenu(InGameMenuFile);
    InGameMenuFile.close();
    InitInGameOverlay(InGameOverlayFile);
    InGameOverlayFile.close();
    InitMenu(MenuFile);
    MenuFile.close();
    InitOptionsMenu(OptionsFile);
    OptionsFile.close();
    InitSavesMenu(SavesFile);
    SavesFile.close();
    filesystem::current_path(old_path);
}
