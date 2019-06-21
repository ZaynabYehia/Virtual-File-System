//
// Created by Mahmoud Rashad on 2019-04-04.
//

#ifndef VIRTUAL_FILE_SYSTEM_INDEXEDALLOCATION_H
#define VIRTUAL_FILE_SYSTEM_INDEXEDALLOCATION_H


#include "blocksAllocation.h"

class indexedAllocation : public blocksAllocation{
    int indexedBlock;
public:
    indexedAllocation();
    bool allocate(int size, freeSpaceManager *spaceManager);
    void deAllocate();
    void read (istream&);
    void write (ostream&);
};


#endif //VIRTUAL_FILE_SYSTEM_INDEXEDALLOCATION_H
