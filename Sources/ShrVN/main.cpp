#include <iostream>
#include <vector>
#include <filesystem>

#include "point.hpp"
#include "bezier.h"
#include "characters.hpp"
#include "character_parserer.h"
#include "character_instantiator.hpp"
#include "in_game_overlay_parameters.hpp"
#include "in_game_overlay_parserer.hpp"
#include "in_game_overlay_interpretor.hpp"
#include "saves_menu_parameters.hpp"
#include "saves_menu_parserer.hpp"
#include "saves_menu_interpertor.h"
#include "main_menu_parameters.hpp"
#include "main_menu_interpretor.hpp"
#include "main_menu_parserer.hpp"
#include "in_game_menu_parserer.hpp"
#include "in_game_menu_parameters.hpp"
#include "in_game_menu_interpretor.hpp"
#include "options_menu_interpretor.h"
#include "options_menu_parserer.hpp"
#include "options_menu_parameters.hpp"
#include "movement_file_parserer.h"
#include "movement.h"
#include "movement_interpretor.h"
#include "init.h"

using namespace std;

void TestBinomial()
{
    int ArrayN[5] = {1,3,5,6,8};
    int ArrayK[5] = {1,4,7,9,10};
    for (int n : ArrayN)
    {
        for (int k : ArrayK)
        {
            int temp_binom = Binomial(n,k);
            if (temp_binom > 0)
            {
                cout << "Binomial avec n = " << n << " et k = " << k << " : " << temp_binom << endl;
            }
        }
    }
}

void TestBezier()
{
    Point Pt1 = {100,200}, Pt2 = {100,400};
    vector<Point> CurvePoint = {Pt1,Pt2};
    for (Point Pt : CurvePoint)
    {
        cout << Pt << endl;
    }
    cout << "Premier Point: " << CalculateOneBezierPoint(0,CurvePoint) << endl;
    cout << "Milieu Point: " << CalculateOneBezierPoint(0.5,CurvePoint) << endl;
    cout << "Dernier Point: " << CalculateOneBezierPoint(1,CurvePoint) << endl;
    Point Pt3 = {200,500};
    CurvePoint.push_back(Pt3);
    cout << "Ajout de Pt3" << endl;
    cout << CalculateAllBezierPoint(CurvePoint,5) << endl;
}

void ShowCharNameColors(const Characters & chr)
{
    cout << "Rouge: " << chr.GetRedValue() << endl;
    cout << "Vert: " << chr.GetGreenValue() << endl;
    cout << "Bleu: " << chr.GetBlueValue() << endl;
    for (int i = 0; i < 50 ; ++i)
        cout << "-" ;
}

void TestCharcters()
{
    filesystem::current_path(filesystem::path("../Scripts/ScriptTest"));
    Characters chr1 = {"Jean"};
    cout << chr1.GetName() << endl;
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Changing the red value to 150" << endl;
    try
    {
        chr1.SetRedValue(150);
    }
    catch(const exception & e)
    {
        cerr << e.what() << endl;
    }
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Setting the red value to 999" << endl;
    try
    {
        chr1.SetRedValue(999);
    }
    catch(const exception & e)
    {
        cerr << e.what() << endl;
    }
    ShowCharNameColors(chr1);
    cout << "\n";
    cout << "Getting the image 'aaaa' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("aaaa") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Adding the image 'bed.webp' to " << chr1.GetName() << endl;
    chr1.AddImage("bed","bed.webp");
    cout << "Getting thte image 'bed.webp' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("bed") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Adding a 'default' image to " << chr1.GetName() << endl;
    chr1.AddImage("default","Akane.png");
    cout << "Getting the default image." << endl << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("default") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
    cout << "Getting the image 'aaaa' from " << chr1.GetName() << endl;
    try
    {
        cout << chr1.GetImage("aaaa") << endl;
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }
}

void TestCharParserer()
{
    filesystem::current_path(filesystem::path("../Scripts/ScriptTest"));
    CharacterInstantiator test;
    CharacterParserer parserer(&test);
    map<string, Characters>& Characters_map =  *(parserer.ParseCharacterFile());
    cout << Characters_map.at("Jean").GetName() << endl;
    cout << Characters_map.at("Jean").GetBlueValue() << endl;
    cout << Characters_map.at("Jean2").GetName() << endl;
    cout << Characters_map.at("Jean2").GetBlueValue() << endl;
    cout << Characters_map.at("Jean2").GetGreenValue() << endl;
    cout << Characters_map.at("Jean2").GetRedValue() << endl;
    cout << Characters_map.at("Jean").GetImage("akane") << endl;
}

void TestFileInit()
{
    filesystem::current_path("init/");
    ofstream file;
    file.open("InGameOverlay.shrvn");
    InitInGameOverlay(file);
    file.close();
    file.open("SavesMenu.shrvn");
    InitSavesMenu(file);
    file.close();
    file.open("MainMenu.shrvn");
    InitMenu(file);
    file.close();
    file.open("InGameMenu.shrvn");
    InitInGameMenu(file);
    file.close();
    file.open("OptionsMenu.shrvn");
    InitOptionsMenu(file);
    file.close();
    filesystem::current_path("../ ");
}

void TestReadInitFiles()
{
    filesystem::current_path("init/");
    ifstream file;
    file.open("InGameOverlay.shrvn");
    InGameOverlayInterpretor igo_interpretor;
    InGameOverlayParserer igo_parse(&igo_interpretor);
    InGameOverlayParameters * ig_Parameters = igo_parse.ReadInGameOverlayParametersFile(file);
    cout << *ig_Parameters << endl;
    file.close();
    file.open("SavesMenu.shrvn"); 
    SavesMenuInterpretor smi_interpretor;
    SavesMenuParserer smi_parse(&smi_interpretor);
    SavesMenuParameters * sm_Parameters = smi_parse.ReadSavesMenuParametersFile(file);
    cout << *sm_Parameters << endl;
    file.close();
    file.open("MainMenu.shrvn");
    MainMenuInterpretor mmi_interpretor;
    MainMenuParserer mmi_parse(&mmi_interpretor);
    MainMenuParameters * mmi_Parameters = mmi_parse.ReadMainMenuParametersFile(file);
    cout << *mmi_Parameters << endl;
    file.close();
    file.open("InGameMenu.shrvn");
    InGameMenuInterpretor igmi_interpretor;
    InGameMenuParserer igmi_parse(&igmi_interpretor);
    InGameMenuParameters * igmi_Parameters = igmi_parse.ReadInGameMenuParametersFile(file);
    cout << *igmi_Parameters << endl;
    file.close();
    file.open("OptionsMenu.shrvn");
    OptionsMenuInterpretor omi_interpretor;
    OptionsMenuParserer omi_parse(&omi_interpretor);
    OptionsMenuParameters * omi_Parameters = omi_parse.ReadOptionMenuParametersFile(file);
    cout << *omi_Parameters << endl;
    file.close();
}

void TestMovementParserer()
{
    ifstream file;
    file.open("Movement.shrvn");
    MovementInterpretor mvt_interpretor;
    MovementFileParserer mvt_parse(&mvt_interpretor);
    map<string,Movement> * map = mvt_parse.FileParserer(file);
    cout << *map << endl;
}

int main()
{
    filesystem::current_path("../Scripts/ScriptTest/");
    // CreateEmptyProject("../Scripts/","new_project");
    // TestFileInit();
    // TestReadInitFiles();
    TestMovementParserer();
    return 0;
}
