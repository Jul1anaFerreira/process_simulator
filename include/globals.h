#ifndef GLOBALS_H
#define GLOBALS_H

#include "process.h"
#include "scheduler.h"

#define MEMORY_SIZE 1000

extern Instruction memory[MEMORY_SIZE];

extern PCB pcb_table[MAX_PROCESSES];

extern int global_time;

extern int TIME_QUANTUM;

extern Queue blocked_queue;

extern int memory_used[MEMORY_SIZE];

extern int process_count;

extern int next_pid;

extern PlannedProgram planned[50];

extern int planned_count;

#endif