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
    void UpdateScriptPos(int nb_lines);
};

#endif // SAVE_H
