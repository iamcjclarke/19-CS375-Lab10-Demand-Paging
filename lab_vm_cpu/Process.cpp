#include "Process.h"

Process::Process(int pid, int priority)
    : pid(pid), priority(priority), cpuBurstRemaining(10), accessIndex(0) {}

bool Process::hasMoreAccesses() const {
    return accessIndex < memoryAccesses.size();
}

std::pair<int, unsigned int> Process::nextAccess() const {
    return memoryAccesses[accessIndex];
}

char Process::nextAccessType() const {
    return accessTypes[accessIndex];
}

void Process::tick(int threadId) {
    if (cpuBurstRemaining > 0) {
        cpuBurstRemaining--;
    }
    if (threadPriorities.find(threadId) != threadPriorities.end()) {
        threadPriorities[threadId] = threadPriorities[threadId];
    }
}

void Process::addThread(int threadId, int threadPriority) {
    threadPriorities[threadId] = threadPriority;
}
