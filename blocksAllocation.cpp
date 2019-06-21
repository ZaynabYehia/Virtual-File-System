//
// Created by Mahmoud Rashad on 2019-04-04.
//

#include "blocksAllocation.h"

blocksAllocation::blocksAllocation() {}
void blocksAllocation::setSpaceManager(freeSpaceManager *spaceManager) {
    this->spaceManager = spaceManager;
}
istream & operator >> (istream &in,  blocksAllocation &allocation) {
    allocation.read(in);
    return in;
}

ostream & operator << (ostream &out,  blocksAllocation &allocation) {
    allocation.write(out);
    return out;
}


