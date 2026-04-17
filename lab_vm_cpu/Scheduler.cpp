#include "Scheduler.h"

Scheduler::Scheduler(SchedulingPolicy policy, int tlbSize)
    : policy(policy), quantum(4) {
    if (policy == SchedulingPolicy::MLFQ) {
        readyQueues.resize(3);
    } else {
        readyQueues.resize(1);
    }
}

void Scheduler::addProcessIfNotExists(int pid) {
    if (processes.find(pid) == processes.end()) {
        processes[pid] = Process(pid, 0);
        enqueueProcess(pid);
    }
}

Process& Scheduler::getProcess(int pid) {
    return processes[pid];
}

void Scheduler::enqueueProcess(int pid, int level) {
    if (level >= (int)readyQueues.size()) {
        level = readyQueues.size() - 1;
    }
    readyQueues[level].push(pid);
}

int Scheduler::getNextProcess() {
    if (policy == SchedulingPolicy::Priority) {
        int bestPid = -1;
        int bestPriority = 1e9;
        for (auto& p : processes) {
            if (p.second.hasMoreAccesses() && p.second.priority < bestPriority) {
                bestPriority = p.second.priority;
                bestPid = p.first;
            }
        }
        return bestPid;
    }

    for (auto& q : readyQueues) {
        if (!q.empty()) {
            int pid = q.front();
            q.pop();
            return pid;
        }
    }
    return -1;
}

void Scheduler::tick() {
}

void Scheduler::adjustPriority(int pid, int threadId) {
    if (processes.find(pid) != processes.end()) {
        processes[pid].threadPriorities[threadId]--;
    }
}
