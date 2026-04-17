#include "TLB.h"

TLB::TLB(int size) : currentTime(0), maxSize(size), hits(0), misses(0) {}

bool TLB::lookup(int pid, int pageNumber, int& frameNumber) {
    currentTime++;
    for (auto& entry : tlbEntries) {
        if (entry.pid == pid && entry.pageNumber == pageNumber) {
            entry.lastUsed = currentTime;
            frameNumber = entry.frameNumber;
            hits++;
            return true;
        }
    }
    misses++;
    return false;
}

void TLB::insert(int pid, int pageNumber, int frameNumber) {
    currentTime++;

    for (auto& entry : tlbEntries) {
        if (entry.pid == pid && entry.pageNumber == pageNumber) {
            entry.frameNumber = frameNumber;
            entry.lastUsed = currentTime;
            return;
        }
    }

    if ((int)tlbEntries.size() < maxSize) {
        tlbEntries.push_back({pid, pageNumber, frameNumber, currentTime});
    } else {
        int lruIndex = 0;
        for (int i = 1; i < (int)tlbEntries.size(); i++) {
            if (tlbEntries[i].lastUsed < tlbEntries[lruIndex].lastUsed) {
                lruIndex = i;
            }
        }
        tlbEntries[lruIndex] = {pid, pageNumber, frameNumber, currentTime};
    }
}

void TLB::printStats() const {
    std::cout << "\nTLB Stats:\n";
    std::cout << "Hits: " << hits << "\n";
    std::cout << "Misses: " << misses << "\n";
}

int TLB::getHits() const {
    return hits;
}

int TLB::getMisses() const {
    return misses;
}
