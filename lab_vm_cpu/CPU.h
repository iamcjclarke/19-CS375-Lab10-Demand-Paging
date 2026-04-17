#ifndef CPU_H
#define CPU_H

#include "Process.h"
#include <iostream>

class CPU {
private:
    int cyclesExecuted;
    int contextSwitches;
    int threadSwitches;

public:
    CPU();

    void execute(Process& p, int threadId);
    void addContextSwitch();
    void addThreadSwitch();
    void printStats() const;

    int getCyclesExecuted() const;
    int getContextSwitches() const;
    int getThreadSwitches() const;
};

#endif
