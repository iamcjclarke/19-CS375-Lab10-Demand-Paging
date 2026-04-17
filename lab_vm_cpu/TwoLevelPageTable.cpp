#include "TwoLevelPageTable.h"

TwoLevelPageTable::TwoLevelPageTable(int pageCount)
    : pageCount(pageCount), pageFaults(0), nextFrame(0) {}

bool TwoLevelPageTable::isInMemory(int pid, int pageNum) const {
    return memoryPages.find({pid, pageNum}) != memoryPages.end();
}

int TwoLevelPageTable::getFrame(int pid, int pageNum) const {
    auto it = secondLevel.find({pid, pageNum});
    if (it != secondLevel.end()) {
        return it->second;
    }
    return -1;
}

void TwoLevelPageTable::loadPage(int pid, int pageNum, int frameNum) {
    int outerPage = pageNum / 4;
    firstLevel[{pid, outerPage}] = 1;
    secondLevel[{pid, pageNum}] = frameNum;
    memoryPages.insert({pid, pageNum});
    pageFaults++;
}

void TwoLevelPageTable::printStats() const {
    std::cout << "\nPage Table Stats:\n";
    std::cout << "Page Faults: " << pageFaults << "\n";
}

int TwoLevelPageTable::getPageFaults() const {
    return pageFaults;
}

int TwoLevelPageTable::allocateFrame() {
    return nextFrame++;
}

