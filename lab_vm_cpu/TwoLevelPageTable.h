#ifndef TWOLEVELPAGETABLE_H
#define TWOLEVELPAGETABLE_H

#include <map>
#include <set>
#include <utility>
#include <iostream>

class TwoLevelPageTable {
private:
    std::map<std::pair<int, int>, int> firstLevel;   // (pid, outer_page) -> second-level marker
    std::map<std::pair<int, int>, int> secondLevel;  // (pid, pageNum) -> frameNum
    std::set<std::pair<int, int>> memoryPages;
    int pageCount;
    int pageFaults;
    int nextFrame;

public:
    TwoLevelPageTable(int pageCount = 16);

    bool isInMemory(int pid, int pageNum) const;
    int getFrame(int pid, int pageNum) const;
    void loadPage(int pid, int pageNum, int frameNum);
    void printStats() const;

    int getPageFaults() const;
    int allocateFrame();
};

#endif

