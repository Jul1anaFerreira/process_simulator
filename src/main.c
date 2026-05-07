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

int process_count = 0;

int next_pid = 2;

PlannedProgram planned[50];

int planned_count = 0;

int main()
{
    init_queue(&blocked_queue);

    read_plan_file("data/plan.txt");

    while(1)
{
    printf("\n===== TIME %d =====\n",
           global_time);

    create_arrived_processes();

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state != TERMINATED)
        {
            execute_process(&pcb_table[i],
                            TIME_QUANTUM);
        }
    }

    int active = 0;

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state != TERMINATED)
        {
            active = 1;
            break;
        }
    }

    if(active == 0)
    {
        break;
    }
}

    printf("\nFinal Process Table:\n");

    for(int i = 0; i < process_count; i++)
    {
        printf("PID=%d PPID=%d STATE=%d VAR=%d\n",
               pcb_table[i].pid,
               pcb_table[i].ppid,
               pcb_table[i].state,
               pcb_table[i].variable);
    }

    return 0;
}