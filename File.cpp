//
// Created by Mahmoud Rashad on 2019-04-02.
//

#include "File.h"

File::File(){}

File::File(string name, string path) {
    this->name = name;
    this->path = path;
    size = 0;
    this->allocationType = 0;
}

string File::getName() {
    return name;
}

int File::getAllocationType() {
    return allocationType;
}
void File::setSpaceManager(freeSpaceManager* spacemanager) {
    allocatedBlocks->setSpaceManager(spacemanager);
}

bool File::allocate(int allocationType, int size, freeSpaceManager *spaceManager) {
    if (allocationType == 1) {
        this->allocationType = 1;
        allocatedBlocks = new contiguousAllocation();
    } else if (allocationType == 2) {
        this->allocationType = 2;
        allocatedBlocks = new linkedAllocation();
    } else if (allocationType == 3) {
        this->allocationType = 3;
        allocatedBlocks = new indexedAllocation();
    } else {
        return false;
    }
    this->size = size;
    return allocatedBlocks->allocate(size, spaceManager);
}

void File::deAllocate() {
    allocatedBlocks->deAllocate();
}

istream & operator >> (istream &in,  File &file) {
    in >> file.name;
    in >> file.path;
    in >> file.size;
    in >> file.allocationType;
   if (file.allocationType == 1) {
        file.allocatedBlocks = new contiguousAllocation();
    } else if (file.allocationType == 2) {
        file.allocatedBlocks = new linkedAllocation();
    } else {
        file.allocatedBlocks = new indexedAllocation();
    }
    in >> *file.allocatedBlocks;
    return in;
}
ostream & operator << (ostream &out,  File &file) {
    out << file.name << '\n';
    out << file.path << '\n';
    out << file.size << '\n';
    out << file.allocationType << '\n';
    out << *file.allocatedBlocks << '\n';
    return out;
}
