//
// Created by Mahmoud Rashad on 2019-04-02.
//

#ifndef VIRTUAL_FILE_SYSTEM_VIRTUALFILESYSTEM_H
#define VIRTUAL_FILE_SYSTEM_VIRTUALFILESYSTEM_H


#include "Directory.h"
#include "freeSpaceManager.h"

class virtualFileSystem {
    int spaceSize;
    Directory *root;
    freeSpaceManager *spaceManager;

public:
    virtualFileSystem();
    virtualFileSystem(int spaceSize);
    void run();
    void load();
    void save();
    bool createFile(string path, int size, int allocationType);
    bool deleteFile(string path);
    bool createFolder(string path);
    bool deleteFolder(string path);
    void deallocateDirectory(Directory directory);
    void displayDiskStructure();
    void displayDiskStatus();
    void DFS(Directory dir, string level);
    vector<string> getNames(string path);
    bool pathExists(vector<string> name);
    bool fileExists(vector<string> path, string file_name);
    void setSpaceManager(Directory* dir);
    int getInput();
};


#endif //VIRTUAL_FILE_SYSTEM_VIRTUALFILESYSTEM_H
