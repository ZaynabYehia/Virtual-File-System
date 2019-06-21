//
// Created by Mahmoud Rashad on 2019-04-04.
//

#ifndef VIRTUAL_FILE_SYSTEM_LINKEDALLOCATION_H
#define VIRTUAL_FILE_SYSTEM_LINKEDALLOCATION_H


#include "blocksAllocation.h"

class linkedAllocation : public blocksAllocation{
    int start;
    int end;
public:
    linkedAllocation();
    bool allocate(int size, freeSpaceManager *spaceManager);
    void deAllocate();
    void read (istream&);
    void write (ostream&);
};


#endif //VIRTUAL_FILE_SYSTEM_LINKEDALLOCATION_H
