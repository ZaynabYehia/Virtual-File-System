//
// Created by Mahmoud Rashad on 2019-04-04.
//

#include "Block.h"

Block::Block() {
    allocated = false;
    nxt = -1;
};


void Block::allocate() {
    allocated = true;
}

void Block::deAllocate() {
    allocated = false;
    nxt = -1;
    allocatedBlocks.clear();
}

bool Block::getStatus() {
    return allocated;
}

void Block::setNxt(int nxt) {
    this->nxt = nxt;
}

int Block::getNxt() {
    return nxt;
}

void Block::setAllocatedBlocks(vector<int> allocatedBlocks) {
    this->allocatedBlocks = allocatedBlocks;
}

vector<int> Block::getAllocatedBlocks() {
    return allocatedBlocks;
}

istream & operator >> (istream &in,  Block &block) {
    in >> block.allocated;
    in >> block.nxt;
    int size;
    in >> size;
    block.allocatedBlocks.resize(size);
    for (int &i : block.allocatedBlocks) {
        in >> i;
    }
    return in;
}

ostream & operator << (ostream &out,  Block &block) {
    out << block.allocated << '\n';
    out << block.nxt << '\n';
    out << block.allocatedBlocks.size() << '\n';
    for (int i = 0; i < block.allocatedBlocks.size(); ++i) {
        out << block.allocatedBlocks[i] << ' ';
    }
    out << '\n';
    return out;
}
