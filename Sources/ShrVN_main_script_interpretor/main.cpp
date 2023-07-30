#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "window.hpp"
#include "in_game_overlay_parameters.hpp"
#include "characters.hpp"
#include "character_parserer.h"
#include "character_instantiator.hpp"
#include "in_game_overlay_parameters.hpp"
#include "in_game_overlay_parserer.hpp"
#include "in_game_overlay_interpretor.hpp"
// #include "saves_menu_parameters.hpp"
// #include "saves_menu_parserer.hpp"
// #include "saves_menu_interpertor.h"
// #include "main_menu_parameters.hpp"
// #include "main_menu_interpretor.hpp"
// #include "main_menu_parserer.hpp"
// #include "in_game_menu_parserer.hpp"
// #include "in_game_menu_parameters.hpp"
// #include "in_game_menu_interpretor.hpp"
// #include "options_menu_interpretor.h"
// #include "options_menu_parserer.hpp"
// #include "options_menu_parameters.hpp"
// #include "bezier.h"
#include "dialogue.h"
#include "parserer_utils.h"
#include "movement.h"
#include "movement_interpretor.h"
#include "movement_file_parserer.h"
#include "init.h"

using namespace std;

void SDLInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << SDL_GetError() << endl;
    }
}

int main(int argc, char* argv[])
{
    SDLInit();
    if (argc <= 1)
    {
        cerr << "ERROR : You need to provide arguments." << endl
             << " -i or --interpret path_to_project to launch the interpretor" << endl
             << " -c or --compile path_to_project to compile a project" << endl
             << " --init path new_project_name to create a new empty project." << endl;
        return -1;
    }
    if (!strcmp(argv[1],"--compile") || !strcmp(argv[1],"-c"))
    {
        throw invalid_argument("The compile feature isn't implemented yet.");
    }
    else if (!strcmp(argv[1],"--interpret") || !strcmp(argv[1],"-i"))
    {
        if (! filesystem::exists(argv[2]))
        {
            cerr << "ERROR : You need to provide an existing path";
            return -2;
        }
    }
    else if (!strcmp(argv[1],"--init"))
    {
        if (! filesystem::exists(argv[2]))
        {
            cerr << "ERROR : You need to provide an existing path";
            return -2;
        }
        filesystem::current_path(argv[2]);
        if (argc < 4)
        {
            cerr << "ERROR : You need to provide a project name";
            return -3;
        }
        CreateEmptyProject(".",argv[3]);
        return 0;
    }
    filesystem::current_path(argv[2]);
    // filesystem::current_path("../Scripts/ScriptTest");
    std::string full_path = filesystem::current_path().generic_string();
    std::string project_name = full_path.substr(full_path.find_last_of("/") + 1);
    ifstream main_script;
    main_script.open("main.shrvn");
    filesystem::current_path("init/");
    ifstream file;
    file.open("InGameOverlay.shrvn");
    InGameOverlayInterpretor igo_interpretor;
    InGameOverlayParserer igo_parse(&igo_interpretor);
    InGameOverlayParameters * ig_Parameters = igo_parse.ReadInGameOverlayParametersFile(file);
    file.close();
    filesystem::current_path("../");
    CharacterInstantiator test;
    CharacterParserer parserer(&test);
    map<string, Characters>& Characters_map =  *parserer.ParseCharacterFile();
    Window fen(project_name);
    fen.Init();
    fen.SetInGameOverlayParameters(ig_Parameters);
    fen.SetFont();
    fen.SetCurrentScreen(InGame);
    // fen.SwitchTextMode();
    MovementInterpretor mvt_interpretor;
    MovementFileParserer mvt_parse(&mvt_interpretor);
    file.open("Movement.shrvn");
    map<string,Movement> * Movement_Map = mvt_parse.FileParserer(file);
    file.close();
    int nb_line = 1;
    bool dbpt, text;
    unsigned short x_value, y_value;
    std::string word, message, temp, char_name, next_word, img, img_path, value, line;
    Characters *current_char;
    Dialogue new_dialogue;
    while (fen.IsOpen() && !main_script.eof())
    {
        text = false;
        while (!text)
        {
            dbpt = false;
            if (CheckEmptyLine(main_script))
            {
                continue;
            }
            getline(main_script,word,' ');
            if (CheckComment(main_script,word))
            {
                continue;
            }
            if (word == "From")
            {
                getline(main_script,char_name,' ');
                if (!Characters_map.contains(char_name))
                {
                    word = char_name;
                    goto wrong_argument;
                }
                current_char = &Characters_map.at(char_name);
                getline(main_script,next_word,' ');
                if (next_word == "Show")
                {
                    getline(main_script,img,' ');
                    img_path = current_char->GetImage(img);
                    if (img_path == Characters::image_not_found)
                    {
                        word = img;
                        goto wrong_argument;
                    }
                    getline(main_script,next_word,' ');
                    if (next_word == "At")
                    {
                        getline(main_script,value,',');
                        x_value = stof(value);
                        getline(main_script,value,'\n');
                        y_value = stof(value);
                        Point pt = {x_value,y_value};
                        fen.AddOnScreenSprite(img_path,pt);
                    }
                    else if (next_word == "With")
                    {
                        getline(main_script,next_word,'\n');
                        if (!Movement_Map->contains(next_word))
                        {
                            word = next_word;
                            goto wrong_argument;
                        }
                        Movement & mvt = Movement_Map->at(next_word);
                        fen.AddOnScreenSprite(img_path,mvt.control_points.front());
                        fen.AddMovementToSprite(img_path,mvt);
                    }
                    else
                    {
                        word = next_word;
                        goto unknown_keyword;
                    }
                }
                else if (next_word == "Hide")
                {
                    getline(main_script,img,'\n');
                    img_path = current_char->GetImage(img);
                    if (img_path == Characters::image_not_found)
                    {
                        word = img;
                        goto wrong_argument;
                    }
                    fen.RemoveOnScreenSprite(img_path);
                }
                else
                {
                    word = next_word;
                    goto unknown_keyword;
                }
            }
            else if (word == "Set")
            {
                getline(main_script,next_word,' ');
                if (next_word != "Background")
                {
                    word = next_word;
                    goto unknown_keyword;
                }
                getline(main_script,next_word,' ');
                if (next_word != "As")
                {
                    word = next_word;
                    goto unknown_keyword;
                }
                getline(main_script,img_path,'\n');
                fen.SetBackgroundImg(img_path);
            }
            else if (word == "Switch")
            {
                getline(main_script,next_word,'\n');
                if (next_word != "Mode")
                {
                    word = next_word;
                    goto unknown_keyword;
                }
                fen.CleanCurrentMessages();
                fen.SwitchTextMode();
            }
            else if (word == "Clear")
            {
                getline(main_script,next_word,'\n');
                if (next_word != "Messages")
                {
                    word = next_word;
                    goto unknown_keyword;
                }
                fen.CleanCurrentMessages();
            }
            else
            {
                if (word.back() == ':')
                {
                    word.pop_back();
                    dbpt = true;
                }
                if (!Characters_map.contains(word))
                {
                    goto unknown_keyword;
                }
                if (dbpt)
                {
                    getline(main_script,temp,'"');
                    getline(main_script,message,'"');
                }
                else
                {
                    getline(main_script,temp,':');
                    getline(main_script,temp,'"');
                    getline(main_script,message,'"');
                }
                getline(main_script,temp,'\n');
                text = true;
                ++nb_line;
            }
        }
        new_dialogue = fen.CreateDialogue(message,Characters_map.at(word));
        fen.AddCurrentDialogue(new_dialogue);
        while (!fen.IsClicked)
        {
            fen.ReactEvent();
            fen.RenderImage();
            std::this_thread::sleep_for(33ms);
        }
        fen.IsClicked = false;
    }
    free(ig_Parameters);
    free(Movement_Map);
    return 0;
unknown_keyword:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + word + " ' in this context");

wrong_argument:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid argument ' " + word + " ' in this context");
}
