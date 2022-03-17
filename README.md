# Page Replacement Algorithms Simulation
An 'LRU' &amp; 'Second Chance' Simulation Implementation for the OS Course in Univesity of Athens

## Description
There are  two given logical address trace files (bzip.trace & gcc.trace) from two processes. The aim of this simulation is to compare how LRU and Second Chance page replacement algorithms would behave by printing some statistics (number of page faults, number of write backs to the secondary memory etc.) .

## Implementation Details
- LRU (Least Recently Used) is implemented by using a queue. The victim paged (the one to be replaced) is popped by this queue. Each time a page is referenced, it's pushed again in the queue (after being deleted from the queue if it's already there).
- Second Chance is implemented by using an array representing the memory frames, what pages are there and whether they have a second chance or not.
- There is a a hashed Page Table for each process

## Compilation & Execution
```
1) make
2)./sim arg1 arg2 arg3 (arg4)
```
- arg1: **LRU** to use LRU (Least Recently Used) page replacement algorithm or **SC** to use Second Chance page replacement algorithm
- arg2: number of main memory frames (positive integer number)
- arg3: ontinuous number of traces to read before start reading from the other file
- arg4: optional, the total number of traces to read (from both files)
