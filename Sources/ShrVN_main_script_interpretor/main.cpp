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
#include "bezier.h"
#include "dialogue.h"
#include "parserer_utils.h"

using namespace std;

void SDLInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << SDL_GetError() << endl;
    }
}

int main()
{
    SDLInit();
    filesystem::current_path("../Scripts/ScriptTest");
    ifstream main_script;
    main_script.open("main.shrvn");
    filesystem::current_path("init/");
    ifstream file;
    file.open("InGameOverlay.shrvn");
    InGameOverlayInterpretor igo_interpretor;
    InGameOverlayParserer igo_parse(&igo_interpretor);
    InGameOverlayParameters * ig_Parameters = igo_parse.ReadInGameOverlayParametersFile(file);
    // cout << *ig_Parameters << endl;
    filesystem::current_path("../");
    CharacterInstantiator test;
    CharacterParserer parserer(&test);
    map<string, Characters>& Characters_map =  *parserer.ParseCharacterFile();
    Window fen("jeu");
    fen.SetInGameOverlayParameters(ig_Parameters);
    fen.Init();
    fen.SetCurrentScreen(InGame);
    // fen.SwitchTextMode();
    fen.SetBackgroundImg("test.png");
    fen.AddOnScreenSprite(Characters_map.at("Jean").GetImage("akane"));
    Point p1(200,400), p2(300,500), p3(440,500), p4(500,300);
    vector<Point> ControlPoints = {p1,p2,p3,p4};
    list<Point> effect = CalculateAllBezierPoint(ControlPoints,50);
    Sprite * CurrentEffect = fen.GetSprite(Characters_map.at("Jean").GetImage("akane"));
    // Dialogue temp2 = fen.CreateDialogue("je suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un test",Characters_map.at("Jean"));
    // fen.AddCurrentDialogue(temp2);
    // temp2 = fen.CreateDialogue("je suis un autre test",Characters_map.at("Jean"));
    CurrentEffect->SetMovement(effect);
    int nb_line = 1;
    bool dbpt, text;
    std::string word, message, temp;
    Dialogue new_dialogue;
    while (fen.IsOpen() && !main_script.eof())
    {
        text = false;
        while (!text)
        {
            dbpt = false;
            if (CheckEmptyLine(main_script))
            {
                ++nb_line;
                continue;
            }
            getline(main_script,word,' ');
            if (CheckComment(main_script,word))
            {
                ++nb_line;
                continue;
            }
            if (word.starts_with("From"))
            {
                cout << "not implemented" << endl;
            }
            else
            {
                if (word.back() == ':')
                {
                    word.pop_back();
                    dbpt = true;
                }
                if (Characters_map.contains(word))
                {
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
                }
                else
                {
                    goto unknown_keyword;
                }
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
        // temp2 = fen.CreateDialogue("je suis un autre test",Characters_map.at("Jean"));
        // fen.AddCurrentDialogue(temp2);
    }
    free(ig_Parameters);
    return 0;
unknown_keyword:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : unknown key word ' " + word + " ' in this context");

wrong_argument:
    throw invalid_argument("ERROR : line " + to_string(nb_line) + " : invalid argument ' " + word + " ' in this context");
}
