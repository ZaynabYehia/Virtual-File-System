//
// Created by Mahmoud Rashad on 2019-04-04.
//

#ifndef VIRTUAL_FILE_SYSTEM_BLOCKSALLOCATION_H
#define VIRTUAL_FILE_SYSTEM_BLOCKSALLOCATION_H

#include "freeSpaceManager.h"

class blocksAllocation {
protected:
    freeSpaceManager *spaceManager;
public:
    blocksAllocation();

    virtual bool allocate(int size, freeSpaceManager *spaceManager) = 0;

    virtual void deAllocate() = 0;
    void setSpaceManager(freeSpaceManager* spaceManager);
    virtual void read (istream&) = 0;
    virtual void write (ostream&) = 0;
    friend istream & operator >> (istream &in,  blocksAllocation &allocation);
    friend ostream & operator << (ostream &out,  blocksAllocation &allocation);
};


#endif //VIRTUAL_FILE_SYSTEM_BLOCKSALLOCATION_H
