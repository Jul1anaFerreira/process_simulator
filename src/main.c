#include <stdio.h>
#include <string.h>

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

int next_pid = 1;

PlannedProgram planned[50];

int planned_count = 0;

int main()
{
    init_queue(&blocked_queue);

    read_plan_file("data/plan.txt");

    char command;

    while(1)
    {
        printf("==============================");
        printf("TIME = %d", global_time);
        printf("============================== 	\n");

        create_arrived_processes();

        printf("Commands: \n");
        printf("E -> Execute \n");
        printf("I -> Interrup \n");
        printf("D -> Long Term Scheduler \n");
        printf("R -> Report \n");
        printf("T -> Terminate Simulator \n");
		printf("Command: ");
        scanf(" %c", &command);

        if(command == 'E')
        {
            PCB *p = fcfs_scheduler();

            if(p != NULL)
            {
                execute_process(p, TIME_QUANTUM);
            }
            else
            {
                printf("No READY processes");
            }
        }

        else if(command == 'I')
        {
            PCB *running = NULL;

            for(int i = 0; i < process_count; i++)
            {
                if(pcb_table[i].state == RUNNING)
                {
                    running = &pcb_table[i];
                    break;
                }
            }

            interrupt_running_process(running);
        }

        else if(command == 'D')
        {
            long_term_scheduler();
        }

        else if(command == 'R')
        {
            print_report();
        }

        else if(command == 'T')
        {
            print_final_statistics();
            break;
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

        if(active == 0 && process_count > 0)
        {
            print_final_statistics();
            break;
        }
    }

    return 0;
}
