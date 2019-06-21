//
// Created by Mahmoud Rashad on 2019-04-02.
//

#ifndef VIRTUAL_FILE_SYSTEM_FREESPACEMANAGER_H
#define VIRTUAL_FILE_SYSTEM_FREESPACEMANAGER_H

#include <iostream>
#include<vector>
#include "Block.h"

using namespace std;

class freeSpaceManager {
    int num_of_blocks;
    vector<Block> blocks;

public:
    freeSpaceManager();
    freeSpaceManager(int num_of_blocks);
    void setSize(int num_of_blocks);
    bool contiguousAllocation(int size, int &start, int &len);
    void contiguousDeAllocation(int start, int len);
    bool linkedAllocation(int size, int &start, int &end);
    void linkedDeAllocation(int start, int end);
    bool indexedAllocation(int size, int &indexed_block);
    void indexedDeAllocation(int indexed_block);
    void displayDiskStatus();
    friend istream & operator >> (istream &in,  freeSpaceManager &spaceManager);
    friend ostream & operator << (ostream &out,  freeSpaceManager &spaceManager);
};


#endif //VIRTUAL_FILE_SYSTEM_FREESPACEMANAGER_H
