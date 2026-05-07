#include <stdio.h>

#include "../include/process.h"
#include "../include/globals.h"
#include "../include/scheduler.h"
#include "../include/memory.h"

Instruction memory[MEMORY_SIZE];

int memory_used[MEMORY_SIZE] = {0};

PCB pcb_table[MAX_PROCESSES];

Queue blocked_queue;

int global_time = 0;

int TIME_QUANTUM = 3;

int process_count = 1;

int next_pid = 2;

int main()
{
    init_queue(&blocked_queue);

    int start = load_program("programs/p1.prg");

    PCB p1 = {
        .pid = 1,
        .ppid = 0,
        .pc = start,
        .start = start,
        .program_size = 3,
        .variable = 0,
        .state = READY
    };

    pcb_table[0] = p1;

    execute_process(&pcb_table[0],
                    TIME_QUANTUM);

    printf("\nVariable = %d\n",
           pcb_table[0].variable);

    printf("CPU Time = %d\n",
           pcb_table[0].cpu_time_used);

    printf("Global Time = %d\n",
           global_time);

    printf("\nTotal Processes: %d\n",
           process_count);

    for(int i = 0; i < process_count; i++)
    {
        printf("PID=%d PPID=%d PC=%d\n",
               pcb_table[i].pid,
               pcb_table[i].ppid,
               pcb_table[i].pc);
    }

    return 0;
}