#include "Clock.h"

Clock::Clock(int frameCount) : clockHand(0) {
    for (int i = 0; i < frameCount; i++) {
        frames.push_back({-1, -1, false, false});
    }
}

int Clock::evictAndReplace(int pid, int pageNum, int& evictedPage, bool isModified) {
    while (true) {
        if (frames[clockHand].pid == -1) {
            frames[clockHand] = {pid, pageNum, true, isModified};
            evictedPage = -1;
            int frameIndex = clockHand;
            clockHand = (clockHand + 1) % frames.size();
            return frameIndex;
        }

        if (!frames[clockHand].referenced && !frames[clockHand].modified) {
            evictedPage = frames[clockHand].pageNumber;
            frames[clockHand] = {pid, pageNum, true, isModified};
            int frameIndex = clockHand;
            clockHand = (clockHand + 1) % frames.size();
            return frameIndex;
        }

        if (frames[clockHand].referenced) {
            frames[clockHand].referenced = false;
        } else if (frames[clockHand].modified) {
            frames[clockHand].modified = false;
        }

        clockHand = (clockHand + 1) % frames.size();
    }
}
