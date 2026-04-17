#ifndef TLB_H
#define TLB_H

#include <vector>
#include <iostream>

class TLBEntry {
public:
    int pid;
    int pageNumber;
    int frameNumber;
    int lastUsed;
};

class TLB {
private:
    std::vector<TLBEntry> tlbEntries;
    int currentTime;
    int maxSize;
    int hits;
    int misses;

public:
    TLB(int size = 4);

    bool lookup(int pid, int pageNumber, int& frameNumber);
    void insert(int pid, int pageNumber, int frameNumber);
    void printStats() const;

    int getHits() const;
    int getMisses() const;
};

#endif
