//
// Created by Mahmoud Rashad on 2019-04-04.
//

#include "linkedAllocation.h"

linkedAllocation::linkedAllocation() {}

bool linkedAllocation::allocate(int size, freeSpaceManager *spaceManager) {
    this->spaceManager = spaceManager;
    return spaceManager->linkedAllocation(size, start, end);
}


void linkedAllocation::deAllocate() {
    spaceManager->linkedDeAllocation(start, end);
}

void linkedAllocation::read(istream &in) {
    in >> start >> end;
}

void linkedAllocation::write(ostream &out) {
    out << start << ' ' << end << '\n';
}