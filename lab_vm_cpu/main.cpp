#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "Process.h"
#include "CPU.h"
#include "TLB.h"
#include "TwoLevelPageTable.h"
#include "Clock.h"
#include "Scheduler.h"

int main(int argc, char* argv[]) {
    int tlbSize = 4;
    if (argc > 1) {
        tlbSize = std::stoi(argv[1]);
    }

    TLB tlb(tlbSize);
    TwoLevelPageTable pageTable(16);
    Clock clockReplacer(4);
    CPU cpu;
    Scheduler scheduler(SchedulingPolicy::RoundRobin, tlbSize);

    std::ifstream infile("input/trace.txt");
    if (!infile) {
        std::cerr << "Could not open input/trace.txt\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        int pid, threadId;
        std::string addressStr;
        char accessType;

        if (!(iss >> pid >> threadId >> addressStr >> accessType)) {
            continue;
        }

        unsigned int address = std::stoul(addressStr, nullptr, 16);
        int pageNum = address / 256;

        scheduler.addProcessIfNotExists(pid);
        Process& proc = scheduler.getProcess(pid);
        proc.memoryAccesses.push_back({threadId, address});
        proc.accessTypes.push_back(accessType);
        proc.addThread(threadId, 0);
    }

    std::ofstream logFile("output_log.txt");
    if (!logFile) {
        std::cerr << "Could not create output_log.txt\n";
        return 1;
    }

    bool workRemaining = true;
    int lastPid = -1;
    int lastThread = -1;

    while (workRemaining) {
        workRemaining = false;

        int pid = scheduler.getNextProcess();
        if (pid == -1) {
            for (int checkPid = 1; checkPid <= 100; checkPid++) {
                try {
                    Process& p = scheduler.getProcess(checkPid);
                    if (p.hasMoreAccesses()) {
                        scheduler.enqueueProcess(checkPid);
                    }
                } catch (...) {
                }
            }
            pid = scheduler.getNextProcess();
            if (pid == -1) break;
        }

        Process& proc = scheduler.getProcess(pid);

        if (proc.hasMoreAccesses()) {
            workRemaining = true;

            auto [threadId, address] = proc.nextAccess();
            char accessType = proc.nextAccessType();
            int pageNum = address / 256;
            int frameNum = -1;

            if (lastPid != -1 && lastPid != pid) {
                cpu.addContextSwitch();
            }
            if (lastThread != -1 && lastThread != threadId) {
                cpu.addThreadSwitch();
            }

            bool tlbHit = tlb.lookup(pid, pageNum, frameNum);
            if (!tlbHit) {
                if (!pageTable.isInMemory(pid, pageNum)) {
                    int evictedPage = -1;
                    frameNum = clockReplacer.evictAndReplace(pid, pageNum, evictedPage, accessType == 'W');
                    pageTable.loadPage(pid, pageNum, frameNum);
                    logFile << "PID " << pid << " Thread " << threadId
                            << " PAGE FAULT: page " << pageNum
                            << " loaded into frame " << frameNum << "\n";
                } else {
                    frameNum = pageTable.getFrame(pid, pageNum);
                }
                tlb.insert(pid, pageNum, frameNum);
            }

            logFile << "PID " << pid << " Thread " << threadId
                    << " Address 0x" << std::hex << address << std::dec
                    << " Page " << pageNum
                    << " Frame " << frameNum
                    << " Access " << accessType
                    << (tlbHit ? " TLB_HIT" : " TLB_MISS")
                    << "\n";

            cpu.execute(proc, threadId);
            proc.accessIndex++;

            if (proc.hasMoreAccesses()) {
                scheduler.enqueueProcess(pid);
            }

            lastPid = pid;
            lastThread = threadId;
        }
    }

    cpu.printStats();
    tlb.printStats();
    pageTable.printStats();

    std::cout << "\nSimulation complete. Log written to output_log.txt\n";
    return 0;
}
