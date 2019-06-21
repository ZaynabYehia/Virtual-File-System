//
// Created by Mahmoud Rashad on 2019-04-04.
//

#ifndef VIRTUAL_FILE_SYSTEM_CONTIGUOUSALLOCATION_H
#define VIRTUAL_FILE_SYSTEM_CONTIGUOUSALLOCATION_H


#include "blocksAllocation.h"

class contiguousAllocation : public blocksAllocation {
    int start;
    int len;
public:
    contiguousAllocation();

    bool allocate(int size, freeSpaceManager *spaceManager);

    void deAllocate();

    void read (istream&);
    void write (ostream&);
};


#endif //VIRTUAL_FILE_SYSTEM_CONTIGUOUSALLOCATION_H
