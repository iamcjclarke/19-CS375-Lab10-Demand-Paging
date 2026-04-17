#ifndef CLOCK_H
#define CLOCK_H

#include <vector>

struct FrameEntry {
    int pid;
    int pageNumber;
    bool referenced;
    bool modified;
};

class Clock {
private:
    std::vector<FrameEntry> frames;
    size_t clockHand;

public:
    Clock(int frameCount = 4);

    int evictAndReplace(int pid, int pageNum, int& evictedPage, bool isModified);
};

#endif

