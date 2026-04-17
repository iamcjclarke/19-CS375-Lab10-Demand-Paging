#include "CPU.h"

CPU::CPU() : cyclesExecuted(0), contextSwitches(0), threadSwitches(0) {}

void CPU::execute(Process& p, int threadId) {
    cyclesExecuted++;
    p.tick(threadId);
}

void CPU::addContextSwitch() {
    contextSwitches++;
}

void CPU::addThreadSwitch() {
    threadSwitches++;
}

void CPU::printStats() const {
    std::cout << "\nCPU Stats:\n";
    std::cout << "Cycles Executed: " << cyclesExecuted << "\n";
    std::cout << "Context Switches: " << contextSwitches << "\n";
    std::cout << "Thread Switches: " << threadSwitches << "\n";
}

int CPU::getCyclesExecuted() const {
    return cyclesExecuted;
}

int CPU::getContextSwitches() const {
    return contextSwitches;
}

int CPU::getThreadSwitches() const {
    return threadSwitches;
}
