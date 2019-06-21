//
// Created by Mahmoud Rashad on 2019-04-04.
//

#ifndef VIRTUAL_FILE_SYSTEM_BLOCK_H
#define VIRTUAL_FILE_SYSTEM_BLOCK_H

#include <iostream>
#include <vector>

using namespace std;

class Block {
    bool allocated;
    int nxt;
    vector<int> allocatedBlocks;
public:
    Block();
    void allocate();
    void deAllocate();
    bool getStatus();
    void setNxt(int nxt);
    int getNxt();
    void setAllocatedBlocks(vector<int> allocatedBlocks);
    vector<int> getAllocatedBlocks();
    friend istream & operator >> (istream &in,  Block &block);
    friend ostream & operator << (ostream &out,  Block &block);
};


#endif //VIRTUAL_FILE_SYSTEM_BLOCK_H
