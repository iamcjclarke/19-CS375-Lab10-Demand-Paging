#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <map>
#include <utility>

class Process {
public:
    int pid;
    int priority;
    int cpuBurstRemaining;
    std::vector<std::pair<int, unsigned int>> memoryAccesses; // (thread_id, address)
    std::vector<char> accessTypes; // R or W
    size_t accessIndex;
    std::map<int, int> threadPriorities;

    Process(int pid = 0, int priority = 0);

    bool hasMoreAccesses() const;
    std::pair<int, unsigned int> nextAccess() const;
    char nextAccessType() const;
    void tick(int threadId);
    void addThread(int threadId, int threadPriority);
};

#endif
