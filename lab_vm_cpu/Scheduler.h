#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <map>
#include <queue>
#include <vector>

enum class SchedulingPolicy { FCFS, RoundRobin, Priority, MLFQ };

class Scheduler {
private:
    SchedulingPolicy policy;
    std::map<int, Process> processes;
    std::vector<std::queue<int>> readyQueues;
    int quantum;

public:
    Scheduler(SchedulingPolicy policy, int tlbSize = 4);

    void addProcessIfNotExists(int pid);
    Process& getProcess(int pid);
    void enqueueProcess(int pid, int level = 0);
    int getNextProcess();
    void tick();
    void adjustPriority(int pid, int threadId);
};

#endif
