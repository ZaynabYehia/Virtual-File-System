//
// Created by Mahmoud Rashad on 2019-04-02.
//

#ifndef VIRTUAL_FILE_SYSTEM_DIRECTORY_H
#define VIRTUAL_FILE_SYSTEM_DIRECTORY_H

#include "File.h"
#include "freeSpaceManager.h";
class Directory {
    string name;
    string path;
    vector<File> files;
    vector<Directory> subDirectories;
    bool deleted;
public:
    Directory();
    Directory(string name, string path);
    string getName();
    int getNumOfDirectories();
    int getNumOfFiles();
    Directory getDirectory(int id);
    void addDirectory(Directory dir);
    Directory * get_directory(int id);
    void addFile(File file);
    File getFile(int id);
    void Delete(int id);
    void DeleteDirectory(int id);
    void setFile(int id, freeSpaceManager *spaceManager);
    void printDirectoryStructure(int level);
    friend istream & operator >> (istream &in,  Directory &directory);
    friend ostream & operator << (ostream &out,  Directory &directory);
};


#endif //VIRTUAL_FILE_SYSTEM_DIRECTORY_H
