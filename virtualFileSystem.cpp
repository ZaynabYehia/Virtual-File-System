//
// Created by Mahmoud Rashad on 2019-04-02.
//

#include "virtualFileSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

virtualFileSystem::virtualFileSystem() {
    spaceManager = new freeSpaceManager();
    root = new Directory();
    load();
}

virtualFileSystem::virtualFileSystem(int spaceSize) {
    spaceManager = new freeSpaceManager(spaceSize);
    root = new Directory("root", "root");
}

void virtualFileSystem::save() {
    ofstream file;
    file.open("DiskStructure.vfs", ios::out);
    file << *spaceManager;
    file << *root;
    file.close();
}

void virtualFileSystem::load() {
    ifstream file;
    file.open("DiskStructure.vfs", ios::in);
    file >> *spaceManager;
    file >> *root;
    file.close();
    setSpaceManager(root);
}
void virtualFileSystem::setSpaceManager(Directory* dir) {
    for(int i = 0; i < dir->getNumOfFiles(); i++)
       dir->setFile(i, spaceManager);
    for(int i = 0; i < dir->getNumOfDirectories(); i++)
        setSpaceManager(dir->get_directory(i));
}
vector<string> virtualFileSystem::getNames(string path) {
    vector<string>ret;
    string tmp = "";
    for(int i = 0; i < path.length(); i++) {
        if (path[i] == '/') {
            ret.push_back(tmp);
            tmp = "";
            continue;
        }
        tmp += path[i];
    }
    ret.push_back(tmp);
    return ret;
}

bool virtualFileSystem::pathExists(vector<string> names) {

    if (names.size() == 0 || names[0] != root->getName())
        return 0;
    Directory cur = *root;
    for (int i = 0; i < names.size() - 1; i++) {
        bool flag = 0;
        for (int j = 0; j < cur.getNumOfDirectories(); j++) {
            if (cur.getDirectory(j).getName() == names[i + 1]) {
                cur = cur.getDirectory(j);
                flag = 1;
                break;
            }
        }
        if (!flag)
            return false;
    }
    return true;
}

bool virtualFileSystem::fileExists(vector<string> path, string file_name) {
    if (path.size() == 0 || path[0] != root->getName())
        return 0;
    Directory cur = *root;
    for (int i = 0; i < path.size() - 1; i++) {
        bool flag = 0;
        for (int j = 0; j < cur.getNumOfDirectories(); j++) {
            if (cur.getDirectory(j).getName() == path[i + 1]) {
                cur = cur.getDirectory(j);
                flag = 1;
                break;
            }
        }
        if (!flag)
            return false;
    }
    for (int j = 0; j < cur.getNumOfFiles(); j++)
        if (cur.getFile(j).getName() == file_name)
            return true;
    return false;
}

bool virtualFileSystem::createFile(string path, int size, int allocationType) {
    vector<string>names = getNames(path);
    string file_name = names.back();
    names.pop_back();
    File file(file_name, path);
    if(pathExists(names) && !fileExists(names, file_name) && file.allocate(allocationType, size, spaceManager)){
        Directory cur = *root, *par = root;
        for(int i = 0; i < names.size() - 1; i++){
            for(int j = 0; j < cur.getNumOfDirectories(); j++){
                if(cur.getDirectory(j).getName() == names[i + 1]){
                    par = par->get_directory(j);
                    cur = cur.getDirectory(j);
                    break;
                }
            }
        }
        par->addFile(file);
        return true;
    }
    return false;

}

bool virtualFileSystem::deleteFile(string path) {
    vector<string> names = getNames(path);
    string file_name = names.back();
    names.pop_back();
    if (fileExists(names, file_name)) {
        Directory cur = *root, *par = root;
        for (int i = 0; i < names.size() - 1; i++) {
            for (int j = 0; j < cur.getNumOfDirectories(); j++) {
                if (cur.getDirectory(j).getName() == names[i + 1]) {
                    cur = cur.getDirectory(j);
                    par = par->get_directory(j);
                    break;
                }
            }
        }
        File file;
        for (int j = 0; j < cur.getNumOfFiles(); j++) {
            if (cur.getFile(j).getName() == file_name) {
                file = cur.getFile(j);
                par->Delete(j);
                break;
            }
        }

        file.deAllocate();
        return true;
    }
    return false;
}
bool virtualFileSystem::createFolder(string path) {
    vector<string> names = getNames(path);
    bool flag = pathExists(names);
    string folder_name = names.back();
    names.pop_back();
    if (!flag && pathExists(names)) {
        Directory cur = *root, *par = root;
        for (int i = 0; i < names.size() - 1; i++) {
            for (int j = 0; j < cur.getNumOfDirectories(); j++) {
                if (cur.getDirectory(j).getName() == names[i + 1]) {
                    cur = cur.getDirectory(j);
                    par = par->get_directory(j);
                    break;
                }
            }
        }
        Directory folder(folder_name, path);
        par->addDirectory(folder);
        return true;
    }
    return false;
}
bool virtualFileSystem::deleteFolder(string path) {
    vector<string> names = getNames(path);
    if (!pathExists(names) || path == "root")
        return false;
    Directory cur = *root, *par = root;
    int id;
    for (int i = 0; i < names.size() - 1; i++) {
        for (int j = 0; j < cur.getNumOfDirectories(); j++) {
            if (cur.getDirectory(j).getName() == names[i + 1]) {
                cur = cur.getDirectory(j);
                id = j;
                if (i < names.size() - 2)
                    par = par->get_directory(j);
                break;
            }
        }
    }
    par->DeleteDirectory(id);
    deallocateDirectory(cur);
    return true;
}

void virtualFileSystem::deallocateDirectory(Directory directory) {
    for(int i = 0; i < directory.getNumOfFiles(); i++)
        directory.getFile(i).deAllocate();
    for(int i = 0; i < directory.getNumOfDirectories(); i++)
        deallocateDirectory(directory.getDirectory(i));
}
void virtualFileSystem::displayDiskStatus() {
    spaceManager-> displayDiskStatus();
}
void virtualFileSystem::DFS(Directory dir, string level){
    cout << level + '*' + dir.getName() << endl;
    for(int i = 0; i < dir.getNumOfFiles(); i++)
        cout << level + "  " + '.' + dir.getFile(i).getName() << endl;
    for(int i = 0; i < dir.getNumOfDirectories(); i++)
        DFS(dir.getDirectory(i), level + "  ");
}
void virtualFileSystem::displayDiskStructure() {
    DFS(*root, "");
}
int virtualFileSystem::getInput(){
    string input;
    cin >> input;
    if(input == "0"){
        cout << "Invalid input\n";
        return getInput();
    }
    for(int i = 0; i < input.size(); i++)
        if(input[i] > '9' || input[i] < '0'){
            cout << "Invalid input\n";
            return getInput();
        }
     int ret;
     stringstream(input)>>ret;
     return ret;
}
void virtualFileSystem::run() {
    string input;
    while (1){
        cout << "1- Create File\n";
        cout << "2- Create Folder\n";
        cout << "3- Delete File\n";
        cout << "4- Delete Folder\n";
        cout << "5- Display disk status\n";
        cout << "6- Display disk structure\n";
        cout << "7- Exit\n";
        int choice;
        choice = getInput();
        if(choice == 7) {
            save();
            return;
        }
        switch(choice){
            case 1: {
                string path;
                int size, type;
                cout << "Path: ";
                cin >> path;
                cout << "\n";
                cout << "Size: ";
                size = getInput();
                cout << "\n";
                cout << "Type: ";
                type = getInput();
                cout << "\n";
               // cout << path << ' ' << size << ' ' << type << endl;
                if(createFile(path, size, type))
                    cout << "SUCCESS!\n";
                else
                    cout << "FAILED!\n";
                break;
            }
            case 2: {
                string path;
                cout << "Path: ";
                cin >> path;
                cout << "\n";
                if(createFolder(path))
                    cout << "SUCCESS!\n";
                else
                    cout << "FAILED!\n";
                break;
            }
            case 3: {
                string path;
                cout << "Path: ";
                cin >> path;
                cout << "\n";
                if(deleteFile(path))
                    cout << "SUCCESS!\n";
                else
                    cout << "FAILED!\n";
                break;
            }
            case 4: {
                string path;
                cout << "Path: ";
                cin >> path;
                cout << "\n";
                if(deleteFolder(path))
                    cout << "SUCCESS!\n";
                else
                    cout << "FAILED!\n";
                break;
            }
            case 5: {
                displayDiskStatus();
                break;
            }
            case 6: {
                displayDiskStructure();
                break;
            }
            default: {
                cout << "Invalid input\n";
            }

        }
    }

}