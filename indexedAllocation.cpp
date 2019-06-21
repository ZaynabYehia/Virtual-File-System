//
// Created by Mahmoud Rashad on 2019-04-04.
//

#include "indexedAllocation.h"

indexedAllocation::indexedAllocation() {}

bool indexedAllocation::allocate(int size, freeSpaceManager *spaceManager) {
    this->spaceManager = spaceManager;
    return spaceManager->indexedAllocation(size, indexedBlock);
}

void indexedAllocation::deAllocate() {
    spaceManager->indexedDeAllocation(indexedBlock);
}


void indexedAllocation::read(istream &in) {
    in >> indexedBlock;
}

void indexedAllocation::write(ostream &out) {
    out << indexedBlock << '\n';
}