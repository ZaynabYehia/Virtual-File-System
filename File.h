//
// Created by Mahmoud Rashad on 2019-04-02.
//

#ifndef VIRTUAL_FILE_SYSTEM_FILE_H
#define VIRTUAL_FILE_SYSTEM_FILE_H

#include <string>
#include <vector>
#include "contiguousAllocation.h"
#include "linkedAllocation.h"
#include "indexedAllocation.h"

using namespace std;

class File {
    string name;
    string path;
    int size;
    blocksAllocation *allocatedBlocks; // leh pointer
    int allocationType;
public:
    File();
    File(string name, string path);
    string getName();
    void setSpaceManager(freeSpaceManager* spacemanager);
    int getAllocationType();
    bool allocate(int allocationType, int size, freeSpaceManager *spaceManager);
    void deAllocate();
    friend istream & operator >> (istream &in,  File &file);
    friend ostream & operator << (ostream &out,  File &file);
};


#endif //VIRTUAL_FILE_SYSTEM_FILE_H
