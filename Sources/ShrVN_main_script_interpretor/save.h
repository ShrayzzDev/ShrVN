#ifndef SAVE_H
#define SAVE_H

#include <fstream>

#include "BufferData.h"
#include "dialogue.h"
#include "SaveData.h"

class Save
{
    BufferData m_buffer;
    SaveData m_user_data;
public:
    Save();
    void ReadBufferFile(std::ifstream & file);
    void ReadSaveFile(std::ifstream & file);
    void SaveBuffer(std::ofstream & file) const;
    void SaveSaveData(std::ofstream & file) const;
    void AddDialogueToBuffer(const Dialogue & dial);
    std::pair<std::string,std::string> & GetLastDialogue();
    void AddOnScreenToBuffer(const std::string & img_path, Point coord);
    void RemoveOnScreenFromBuffer(const std::string & img_path);
    void UpdateScriptPos(long long script_pos);
    void UpdateBackground(const std::string & bg_path);
    void ClearCurrentDial();
    void SetTextMode(text_mode txt_mode);
    text_mode GetTextMode();
    long long GetScriptLine();
    const std::string & GetBgPath();
    unsigned short GetNbCurrentDial();
    std::list<std::pair<std::string,std::string>> & GetDialogues();
    std::map<std::string,Point> & GetOnScreen();
    friend std::ostream & operator<<(std::ostream & os, Save & save);
};

std::ostream & operator<<(std::ostream & os, Save & save);

#endif // SAVE_H
