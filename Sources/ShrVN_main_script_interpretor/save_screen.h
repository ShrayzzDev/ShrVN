#ifndef SAVE_SCREEN_H
#define SAVE_SCREEN_H

#include <list>
#include <vector>
#include <map>

#include <SDL.h>

#include "saves_menu_parameters.hpp"
#include "CurrentScreen.h"
#include "SaveMenuState.h"
#include "save_button.h"
#include "button.hpp"
#include "save.h"

class SaveScreen : public CurrentScreen
{
    SDL_Texture * m_background_img;
    SavesMenuParameters * m_smp;
    std::list<Button> m_pages;
    std::vector<button::SaveButton> m_save_buttons;
    std::map<unsigned short,std::map<unsigned short,Save>> m_saves;
    unsigned short m_current_page = 1;
    SaveMenuState m_sms;
public:
    Save m_current_save;
    SaveScreen(SavesMenuParameters * smp = nullptr);
    SavesMenuParameters * GetSmp() const;
    SDL_Texture * GetBgImg() const;
    Save & GetCurrentSave();
    Save & GetSave(unsigned short slot, unsigned short page);
    std::vector<button::SaveButton> & GetMenuButtons();
    void InitScreen(SDL_Renderer * rend, Window * win);
    void InitBtn(Window * win);
    void UpdateButton(unsigned short slot_nb, SDL_Renderer * rend, Window * win);
    void WriteSaveData(const std::string & project_name, unsigned short page, unsigned short slot);
    bool ReadSaveData(const std::string & project_name, unsigned short page, unsigned short slot, Save & save);
    void ReadAllSaveData(const std::string & project_name);
    void SetBackgroundImg(const std::string &bg_img, SDL_Renderer * rend);
    void SetMenuState(SaveMenuState sms);
    void SetCurrentPage(unsigned current_page_nb);
    bool SetCurrentSave(unsigned short page, unsigned short index);
    unsigned short GetCurrentPage();
    SaveMenuState GetSaveMenuState();
    void ReactEvent(Window *win, SDL_Event &event) override;
    void Click(Window * win);
    short WhichSaveBtn(short mouse_x, short mouse_y);
    short WhichPageBtn(short mouse_x, short mouse_y);
    void RenderWindow(SDL_Renderer *rend, unsigned short window_length, unsigned short window_height) override;
};

void MenuPageButton(Window * win, CurrentScreen * cs);
void SaveButtonClicked(Window * win, CurrentScreen * cs);

#endif // SAVE_SCREEN_H
