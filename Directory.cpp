//
// Created by Mahmoud Rashad on 2019-04-02.
//

#include "Directory.h"

Directory::Directory() {}

Directory::Directory(string name, string path) {
    this->name = name;
    this->path = path;
}

string Directory::getName() {
    return name;
}

int Directory::getNumOfDirectories() {
    return subDirectories.size();
}
int Directory::getNumOfFiles() {
    return files.size();
}
void Directory::addDirectory(Directory dir) {
    subDirectories.push_back(dir);
}
Directory Directory::getDirectory(int idx){
    return subDirectories[idx];
}
Directory* Directory::get_directory(int idx) {
    return &subDirectories[idx];
}
void Directory::addFile(File file) {
    files.push_back(file);
}
File Directory::getFile(int idx) {
    return files[idx];
}
void Directory::Delete(int idx) {
    files.erase(files.begin() + idx);
}
void Directory::DeleteDirectory(int idx) {
    subDirectories.erase(subDirectories.begin() + idx);
}
void Directory::setFile(int id, freeSpaceManager *spaceManager) {
    files[id].setSpaceManager(spaceManager);
}
istream & operator >> (istream &in,  Directory &directory) {
    in >> directory.name;
    in >> directory.path;
    int size;
    in >> size;
    directory.files.resize(size);
    for (File &file : directory.files) {
        in >> file;
    }
    in >> size;
    directory.subDirectories.resize(size);
    for (Directory &subDir : directory.subDirectories) {
        in >> subDir;
    }
    return in;
}
ostream & operator << (ostream &out,  Directory &directory) {
    out << directory.name << '\n';
    out << directory.path << '\n';
    out << directory.files.size() << '\n';
    for (File &file : directory.files) {
        out << file << '\n';
    }
    out << directory.subDirectories.size();
    for (Directory &subDir : directory.subDirectories) {
        out << subDir << '\n';
    }
    out << '\n';
    return out;
}