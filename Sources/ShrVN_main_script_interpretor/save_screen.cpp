#include <iostream>
#include <filesystem>
#include <cstdlib>

#include <SDL_image.h>

#include "SaveMenuState.h"
#include "save_screen.h"
#include "window.hpp"

SaveScreen::SaveScreen(SavesMenuParameters * smp)
    :m_smp{smp}
{

}

SavesMenuParameters *SaveScreen::GetSmp() const
{
    return m_smp;
}

SDL_Texture *SaveScreen::GetBgImg() const
{
    return m_background_img;
}

Save & SaveScreen::GetCurrentSave()
{
    return m_current_save;
}

void SaveScreen::InitScreen(SDL_Renderer * rend, Window * win)
{
    SetBackgroundImg(m_smp->m_background_image,rend);
    ReadAllSaveData(win->GetName());
    InitBtn(rend);
}

void SaveScreen::SetBackgroundImg(const std::string &bg_img, SDL_Renderer * rend)
{
    std::filesystem::path full_path = std::filesystem::current_path().generic_string() + "/images/" + bg_img;
    if (! std::filesystem::exists(full_path))
    {
        throw std::invalid_argument("ERROR : Couldn't find the " + bg_img);
    }
    if (m_background_img != nullptr)
    {
        SDL_DestroyTexture(m_background_img);
    }
    m_background_img = IMG_LoadTexture(rend,full_path.generic_string().c_str());
    if (m_background_img == nullptr)
    {
        throw std::invalid_argument("ERROR : Couldn't open file " + bg_img);
    }
}

void SaveScreen::SetMenuState(SaveMenuState sms)
{
    m_sms = sms;
}

void SaveScreen::SetCurrentPage(unsigned int current_page_nb)
{
    m_current_page = current_page_nb;
}

bool SaveScreen::SetCurrentSave(unsigned short page, unsigned short index)
{
    try
    {
        m_current_save = m_saves.at(page).at(index);
        std::cout << "je crash pas" << std::endl;
    }
    catch (std::out_of_range & e)
    {
        return false;
    }
    return true;
}

unsigned short SaveScreen::GetCurrentPage()
{
    return m_current_page;
}

SaveMenuState SaveScreen::GetSaveMenuState()
{
    return m_sms;
}

void SaveScreen::InitBtn(SDL_Renderer *rend)
{
    int x_coord = 450, y_coord = 150;
    for (int i = 0; i < m_smp->m_nb_pages; ++i)
    {
        SDL_Rect rect = {x_coord,y_coord,40,40};
        SDL_Color col = {255,255,255,255};
        Button btn = {"btn_pg" + std::to_string(i+1),std::to_string(i+1),col,rect,rend};
        btn.m_WhenPressed = MenuPageButton;
        m_pages.push_back(btn);
        x_coord += 75;
    }
    x_coord = 450;
    y_coord = 175;
    for (int i = 0; i < m_smp->m_nb_saves_per_pages; ++i)
    {
        SDL_Rect rect = {x_coord,y_coord,500,155};
        button::SaveButton sb = {rect};
        sb.m_WhenPressed = SaveButtonClicked;
        try
        {
            Save * save = new Save();
            *save = m_saves.at(m_current_page).at(i+1);
            sb.SetSave(save,rend);
        }
        catch (std::out_of_range & e)
        {

        }
        m_save_buttons.push_back(sb);
        if (i%2 == 1)
        {
            x_coord = 450;
            y_coord += 180;
        }
        else
        {
            x_coord += 600;
        }
    }
}

void SaveScreen::WriteSaveData(const std::string & project_name, unsigned short page, unsigned short slot)
{
    std::string old_path = std::filesystem::current_path().generic_string();
#ifdef _WIN64
    std::string save_path = getenv("appdata");
    save_path += "/../Local/";
    std::filesystem::current_path(save_path);
    save_path += project_name;
#endif
    if (!std::filesystem::exists(save_path))
    {
        std::filesystem::create_directory(project_name);
        std::filesystem::current_path(project_name);
        std::filesystem::create_directory("buffer");
        std::filesystem::current_path("buffer");
        std::filesystem::create_directory(std::to_string(page));
        std::filesystem::create_directory("../savedata");
        std::filesystem::current_path("../savedata");
        std::filesystem::create_directory(std::to_string(page));
        std::filesystem::current_path("..");
    }
    else
    {
        std::filesystem::current_path(project_name);
        if (!std::filesystem::exists("savedata/"))
        {
            std::filesystem::create_directory("savedata");
        }
        if (!std::filesystem::exists("buffer/"))
        {
            std::filesystem::create_directory("buffer");
        }
        if (!std::filesystem::exists("savedata/"+std::to_string(page)))
        {
            std::filesystem::current_path("savedata");
            std::filesystem::create_directory(std::to_string(page));
            std::filesystem::current_path("../buffer");
            std::filesystem::create_directory(std::to_string(page));
            std::filesystem::current_path("..");
        }
    }
    std::ofstream save_file;
    std::filesystem::current_path("savedata/"+std::to_string(page));
    save_file.open(std::to_string(slot));
    m_current_save.SaveSaveData(save_file);
    save_file.close();
    std::filesystem::current_path("../../buffer/"+std::to_string(page));
    save_file.open(std::to_string(slot));
    m_current_save.SaveBuffer(save_file);
    save_file.close();
    std::filesystem::current_path(old_path);
}

bool SaveScreen::ReadSaveData(const std::string & project_name, unsigned short page, unsigned short slot, Save & save)
{
    std::string old_path = std::filesystem::current_path().generic_string();
#ifdef _WIN64
    std::string save_path = getenv("appdata");
    save_path += "/../Local/";
    std::filesystem::current_path(save_path);
    save_path += project_name;
#endif
    if (!std::filesystem::exists(save_path))
    {
        std::filesystem::current_path(old_path);
        return false;
    }
    std::filesystem::current_path(save_path);
    save_path += "/savedata/";
    if (!std::filesystem::exists(save_path))
    {
        std::filesystem::current_path(old_path);
        return false;
    }
    save_path += std::to_string(page) + '/';
    if (!std::filesystem::exists(save_path))
    {
        std::filesystem::current_path(old_path);
        return false;
    }
    std::string full_save_path = save_path + std::to_string(slot);
    if (!std::filesystem::exists(full_save_path))
    {
        std::filesystem::current_path(old_path);
        return false;
    }
    std::ifstream file;
    file.open(full_save_path);
    save.ReadSaveFile(file);
    file.close();
    full_save_path = save_path + "../../buffer/" + std::to_string(page) + "/" + std::to_string(slot);
    file.open(full_save_path);
    save.ReadBufferFile(file);
    file.close();
    std::filesystem::current_path(old_path);
    return true;
}

void SaveScreen::ReadAllSaveData(const std::string &project_name)
{
    for (int i = 1; i <= m_smp->m_nb_pages; ++i)
    {
        std::map<unsigned short,Save> map_save;
        m_saves.emplace(std::pair<unsigned short,std::map<unsigned short,Save>>(i,map_save));
        for (int k = 1; k <= m_smp->m_nb_saves_per_pages; ++k)
        {
            Save save;
            if (ReadSaveData(project_name,i,k,save))
            {
                m_saves.at(i)[k] = save;
            }
        }
    }
}

void SaveScreen::ReactEvent(Window *win, SDL_Event &event)
{
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        switch (event.button.clicks) {
        case SDL_BUTTON_LEFT:
            Click(win);
            break;
        }
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
        case SDLK_ESCAPE:
            win->SetCurrentScreen(in_game);
            break;
        case SDLK_RETURN:
            Click(win);
            break;
        }
        break;
    }
}

void SaveScreen::Click(Window * win)
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    for (auto & btn : m_pages)
    {
        if (btn.IsWithinBound(x,y))
        {
            btn.m_WhenPressed(nullptr,this);
        }
    }
    for (auto & btn : m_save_buttons)
    {
        if (btn.IsWithinBound(x,y))
        {
            btn.m_WhenPressed(win,this);
        }
    }
}

short SaveScreen::WhichSaveBtn(short mouse_x, short mouse_y)
{
    int i = 0;
    for (auto & btn : m_save_buttons)
    {
        if (btn.IsWithinBound(mouse_x,mouse_y))
        {
            return i;
        }
        ++i;
    }
    return -1;
}

short SaveScreen::WhichPageBtn(short mouse_x, short mouse_y)
{
    int i = 0;
    for (auto & btn : m_pages)
    {
        if (btn.IsWithinBound(mouse_x,mouse_y))
        {
            return i;
        }
        ++i;
    }
    return -1;
}

void SaveScreen::RenderWindow(SDL_Renderer *rend, unsigned short window_length, unsigned short window_height)
{
    SDL_RenderCopy(rend,m_background_img,NULL,NULL);
    int x,y;
    SDL_GetMouseState(&x,&y);
    for (auto & btn : m_pages)
    {
        btn.RenderButton(rend,x,y,false);
    }
    for (auto & btn : m_save_buttons)
    {
        btn.RenderBtn(rend,x,y);
    }
}

void MenuPageButton(Window *win, CurrentScreen *cs)
{
    SaveScreen * sc = dynamic_cast<SaveScreen*>(cs);
    if (sc == nullptr)
    {
        return;
    }
    int x,y;
    SDL_GetMouseState(&x,&y);
    short pagenb = sc->WhichPageBtn(x,y);
    if (pagenb == -1)
    {
        return;
    }
    sc->SetCurrentPage(pagenb);
}

void SaveButtonClicked(Window * win, CurrentScreen * cs)
{
    SaveScreen * sc = dynamic_cast<SaveScreen*>(cs);
    if (sc == nullptr)
    {
        return;
    }
    int x,y;
    SDL_GetMouseState(&x,&y);
    short savenb = sc->WhichSaveBtn(x,y);
    if (savenb == -1)
    {
        return;
    }
    std::string prj_name = win->GetName();
    unsigned short nb_page = sc->GetCurrentPage();
    switch (sc->GetSaveMenuState()) {
    case Saving:
        sc->WriteSaveData(prj_name,nb_page,savenb+1);
        break;
    case Loading:
        if (sc->SetCurrentSave(nb_page,savenb+1))
        {
            InGameWindow & igw = win->GetIgw();
            igw.m_sl->LoadSave(*igw.GetCurrentScript(),&igw,sc->GetCurrentSave(),*win->GetCharMap(),win->GetRenderer());
        }
        break;
    }
}
