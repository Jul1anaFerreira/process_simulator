#include <stdio.h>

#include "../include/process.h"
#include "../include/globals.h"
#include "../include/scheduler.h"

Instruction memory[MEMORY_SIZE];

PCB pcb_table[MAX_PROCESSES];

Queue blocked_queue;

int global_time = 0;

int TIME_QUANTUM = 3;

int main()
{
    memory[0] = (Instruction){'M', 100, ""};
    memory[1] = (Instruction){'B', 0, ""};
    memory[2] = (Instruction){'A', 20, ""};
    memory[3] = (Instruction){'T', 0, ""};

    PCB p1 = {
        .pid = 1,
        .ppid = 0,
        .pc = 0,
        .variable = 0,
        .state = READY
    };

    init_queue(&blocked_queue);

    execute_process(&p1, TIME_QUANTUM);

    printf("\nVariable = %d\n", p1.variable);

    printf("CPU Time = %d\n", p1.cpu_time_used);

    printf("Global Time = %d\n", global_time);

    return 0;
}