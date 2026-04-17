import re
import matplotlib.pyplot as plt

page_faults = 0
tlb_hits = 0
tlb_misses = 0
events = []

with open("output_log.txt", "r") as f:
    for i, line in enumerate(f):
        if "PAGE FAULT" in line:
            page_faults += 1
            events.append((i, 1))
        if "TLB_HIT" in line:
            tlb_hits += 1
        if "TLB_MISS" in line:
            tlb_misses += 1

print("Page Faults:", page_faults)
print("TLB Hits:", tlb_hits)
print("TLB Misses:", tlb_misses)

x = list(range(len(events)))
y = [e[1] for e in events]

plt.figure(figsize=(10, 4))
plt.plot(x, y, marker='o')
plt.title("Page Fault Timeline")
plt.xlabel("Fault Event Number")
plt.ylabel("Page Fault")
plt.grid(True)
plt.savefig("page_fault_timeline.png")
print("Saved graph to page_fault_timeline.png")
