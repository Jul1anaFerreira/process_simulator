#include <stdio.h>
#include <string.h>

#include "../include/process.h"
#include "../include/globals.h"
#include "../include/scheduler.h"
#include "../include/memory.h"

void execute_instruction(PCB *p, Instruction instr)
{
    switch(instr.ins)
    {
        case 'M':
            p->variable = instr.n;
            break;

        case 'A':
            p->variable += instr.n;
            break;

        case 'S':
            p->variable -= instr.n;
            break;

        case 'B':
            p->state = BLOCKED;
            printf("Process %d blocked\n", p->pid);
            break;

        case 'T':
           p->state = TERMINATED;
           p->end_time = global_time;
           free_program_memory(p->start,
                               p->program_size);
                               
           break;

        case 'C':
           execute_C_instruction(p,
                          instr.n);
            break;

        case 'L':
           execute_L_instruction(p,
                          instr.nome);
            return;

        default:
            printf("Unknown instruction: %c\n", instr.ins);
    }
}

void execute_process(PCB *p, int quantum)
{
    p->state = RUNNING;

    printf("\nExecuting PID %d\n", p->pid);

    for(int i = 0; i < quantum; i++)
    {
        Instruction instr = memory[p->pc];

        printf("PC=%d | INS=%c %d\n",
               p->pc,
               instr.ins,
               instr.n);

        execute_instruction(p, instr);

        if(instr.ins == 'L')
        {
            continue;
        }

        p->cpu_time_used++;

        global_time++;

        if(p->state == BLOCKED ||
           p->state == TERMINATED)
        {
            break;
        }

        p->pc++;
    }

    if(p->state == RUNNING)
    {
        p->state = READY;
    }
    else if(p->state == BLOCKED)
    {
        enqueue(&blocked_queue, p->pid);
    }

  printf("PID=%d | VAR=%d | STATE=%d | CPU=%d\n",
       p->pid,
       p->variable,
       p->state,
       p->cpu_time_used);


}

void context_switch(PCB *old_p, PCB *new_p)
{
    if(old_p != NULL &&
       old_p->state == RUNNING)
    {
        old_p->state = READY;
    }

    new_p->state = RUNNING;

    printf("\nContext switch: PID %d -> PID %d\n",
           old_p ? old_p->pid : -1,
           new_p->pid);
}

void unblock_process()
{
    if(is_empty(&blocked_queue))
    {
        return;
    }

    int pid = dequeue(&blocked_queue);

    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        if(pcb_table[i].pid == pid)
        {
            pcb_table[i].state = READY;

            printf("Process %d unblocked\n", pid);

            break;
        }
    }
}

