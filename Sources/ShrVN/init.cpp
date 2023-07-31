#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "init.h"
#include "in_game_menu_parameters.hpp"
#include "in_game_overlay_parameters.hpp"
#include "main_menu_parameters.hpp"
#include "options_menu_parameters.hpp"
#include "saves_menu_parameters.hpp"

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
    ofstream CharFile("Characters.shrvn"), MainScript("MainScript.shrvn"), Movement("Movement.shrvn");
    CharFile.close();
    MainScript.close();
    Movement.close();
    filesystem::current_path("init/");
    ofstream InGameMenuFile("InGameMenu.shrvn"), InGameOverlayFile("InGameOverlay.shrvn"), MenuFile("Menu.shrvn"), OptionsFile("OptionsMenu.shrvn"), SavesFile("SavesMenu.shrvn");
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
