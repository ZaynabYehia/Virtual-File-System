//
// Created by Mahmoud Rashad on 2019-04-04.
//

#include "contiguousAllocation.h"


contiguousAllocation::contiguousAllocation(){}

bool contiguousAllocation::allocate(int size, freeSpaceManager *spaceManager) {
    this->spaceManager = spaceManager;
    return spaceManager->contiguousAllocation(size, start, len);
}

void contiguousAllocation::deAllocate() {
    spaceManager->contiguousDeAllocation(start, len);
}

void contiguousAllocation::read(istream &in) {
    in >> start >> len;
}

void contiguousAllocation::write(ostream &out) {
    out << start << ' ' << len << '\n';
}