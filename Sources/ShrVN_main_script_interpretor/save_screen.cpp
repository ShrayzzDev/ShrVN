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

void SaveScreen::InitScreen(SDL_Renderer * rend)
{
    SetBackgroundImg(m_smp->m_background_image,rend);
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

void SaveScreen::SetCurrentSave(Save save)
{
    std::cout << "GNEEEEEEEEEEEEEEEE" << std::endl;
    m_current_save = save;
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
        try
        {
            m_saves.at(m_current_page).at(i);
        }
        catch (std::out_of_range & e)
        {
            button::SaveButton sb = {rect,nullptr};
            sb.m_WhenPressed = SaveButtonClicked;
            m_save_buttons.push_back(sb);
        }
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
    std::cout << std::filesystem::current_path() << std::endl;
    save_file.open(std::to_string(slot));
    m_current_save.SaveBuffer(save_file);
    save_file.close();
    std::filesystem::current_path(old_path);
}

Save SaveScreen::ReadSaveData(const std::string & project_name, unsigned short page, unsigned short slot)
{
    std::cout << "je suis la" << std::endl;
    Save temp;
    return temp;
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

unsigned short SaveScreen::WhichSaveBtn(short mouse_x, short mouse_y)
{
    int i = 1;
    for (auto & btn : m_save_buttons)
    {
        if (btn.IsWithinBound(mouse_x,mouse_y))
        {
            return i;
        }
        ++i;
    }
    return 0;
}

unsigned short SaveScreen::WhichPageBtn(short mouse_x, short mouse_y)
{
    int i = 1;
    for (auto & btn : m_pages)
    {
        if (btn.IsWithinBound(mouse_x,mouse_y))
        {
            return i;
        }
        ++i;
    }
    return 0;
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
        btn.RenderBtn(rend);
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
    unsigned int pagenb = sc->WhichPageBtn(x,y);
    if (!pagenb)
    {
        return;
    }
    sc->SetCurrentPage(pagenb);
    std::cout << pagenb << std::endl;
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
    unsigned int savenb = sc->WhichSaveBtn(x,y);
    if (!savenb)
    {
        return;
    }
    std::string prj_name = win->GetName();
    unsigned short nb_page = sc->GetCurrentPage();
    switch (sc->GetSaveMenuState()) {
    case Saving:
        sc->WriteSaveData(prj_name,nb_page,savenb);
        break;
    case Loading:
        Save save = sc->ReadSaveData(prj_name,nb_page,savenb);
        sc->SetCurrentSave(save);
        break;
    }
}
