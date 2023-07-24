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
    // fen.SetTextMode(NVL);
    fen.SetBackgroundImg("test.png");
    fen.AddOnScreenSprite(Characters_map.at("Jean").GetImage("akane"));
    Point p1(200,400), p2(300,500), p3(440,500), p4(500,300);
    vector<Point> ControlPoints = {p1,p2,p3,p4};
    list<Point> effect = CalculateAllBezierPoint(ControlPoints,50);
    Sprite * CurrentEffect = fen.GetSprite(Characters_map.at("Jean").GetImage("akane"));
    fen.TestAddText(Characters_map,"je suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un testje suis un test" );
    fen.TestAddText(Characters_map,"je suis un autre test");
    CurrentEffect->SetMovement(effect);
    while (fen.IsOpen())
    {
        fen.ReactEvent();
        fen.RenderImage();
        std::this_thread::sleep_for(33ms);
    }
    free(ig_Parameters);
    return 0;
}
