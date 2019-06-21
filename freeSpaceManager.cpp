//
// Created by Mahmoud Rashad on 2019-04-02.
//

#include "freeSpaceManager.h"
#include <iostream>

freeSpaceManager::freeSpaceManager() {}

freeSpaceManager::freeSpaceManager(int num_of_blocks) {
    this->num_of_blocks = num_of_blocks;
    blocks.resize(num_of_blocks);
}

void freeSpaceManager::setSize(int num_of_blocks) {
    this->num_of_blocks = num_of_blocks;
    blocks.resize(num_of_blocks);
}

bool freeSpaceManager::contiguousAllocation(int size, int &start, int &len) {
    int mx = 0, cur = 0, st = 0, optimal_start = 0;
    for(int i = 0; i < blocks.size(); i++){
        if(blocks[i].getStatus())
            st = i + 1, cur = 0;
        else
            cur++;
        if(cur > mx){
            optimal_start = st;
            mx = cur;
        }
    }
    if(mx < size)
        return false;
    start = optimal_start;
    len = size;
    for(int i = optimal_start; i < optimal_start + size; i++)
        blocks[i].allocate();
    return true;
}

void freeSpaceManager::contiguousDeAllocation(int start, int len) {
    for (int i = start; i < start + len; ++i) {
        blocks[i].deAllocate();
    }
}

bool freeSpaceManager::linkedAllocation(int size, int &start, int &end) {
    vector<int> free_blocks;
    for(int i = 0; i < blocks.size(); i++)
        if(!blocks[i].getStatus())
            free_blocks.push_back(i);
    if(free_blocks.size() < size)
        return false;
    if (size > 0) {
        blocks[free_blocks[size - 1]].setNxt(-1);
        blocks[free_blocks[size - 1]].allocate();
        start = free_blocks[0];
        end = free_blocks[size - 1];
        for(int i = 0; i < size - 1; i++) {
            blocks[free_blocks[i]].setNxt(free_blocks[i + 1]);
            blocks[free_blocks[i]].allocate();
        }
    }
    return true;
}

void freeSpaceManager::linkedDeAllocation(int start, int end) {
    int i = start;
    while (i != end) {
        blocks[i].deAllocate();
        i = blocks[i].getNxt();
    }
    blocks[end].deAllocate();
}

bool freeSpaceManager::indexedAllocation(int size, int &indexed_block) {
    vector<int>free_blocks;
    for(int i = 0; i < blocks.size(); i++)
        if(!blocks[i].getStatus())
            free_blocks.push_back(i);
    if(free_blocks.size() < size + 1)
        return false;
    indexed_block = free_blocks[0];
    blocks[free_blocks[0]].allocate();
    vector<int> allocatedBlocks;
    for(int i = 1; i < size + 1; i++){
        allocatedBlocks.push_back(free_blocks[i]);
        blocks[free_blocks[i]].allocate();
    }
    blocks[free_blocks[0]].setAllocatedBlocks(allocatedBlocks);
    return true;
}

void freeSpaceManager::indexedDeAllocation(int indexed_block) {
    vector<int> allocatedBlocks = blocks[indexed_block].getAllocatedBlocks();
    for (int i = 0; i < allocatedBlocks.size(); ++i) {
        blocks[allocatedBlocks[i]].deAllocate();
    }
    blocks[indexed_block].deAllocate();
}
void freeSpaceManager::displayDiskStatus() {
    int empty = 0;
    for (int i = 0; i < num_of_blocks; i++) {
        empty += !blocks[i].getStatus();
    }
    cout << "Empty space: "
        << empty << '\n';
    cout << "Empty blocks: \n";
    for (int i = 0; i < num_of_blocks; i++) {
        if (!blocks[i].getStatus()) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    cout << "Allocated space: "
        << num_of_blocks - empty << '\n';
    for (int i = 0; i < num_of_blocks; i++) {
        if (blocks[i].getStatus()) {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

istream & operator >> (istream &in, freeSpaceManager &spaceManager) {
    int num_of_blocks;
    in >> num_of_blocks;
    spaceManager.setSize(num_of_blocks);
    for (Block &block : spaceManager.blocks) {
        in >> block;
    }
    return in;
}

ostream & operator << (ostream &out,  freeSpaceManager &spaceManager) {
    out << spaceManager.num_of_blocks << '\n';
    for (Block &block : spaceManager.blocks) {
        out << block << '\n';
    }
    out << '\n';
    return out;
}