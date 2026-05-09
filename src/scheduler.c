#include <stdio.h>

#include "../include/scheduler.h"
#include "../include/process.h"
#include "../include/globals.h"

void init_queue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

int is_empty(Queue *q)
{
    return q->rear < q->front;
}

void enqueue(Queue *q, int value)
{
    if(q->rear >= QUEUE_SIZE - 1)
    {
        return;
    }

    q->rear++;

    q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
    if(is_empty(q))
    {
        return -1;
    }

    int value = q->items[q->front];

    q->front++;

    return value;
}

PCB* fcfs_scheduler()
{
    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == READY)
        {
            return &pcb_table[i];
        }
    }

    return NULL;
}

PCB* priority_scheduler()
{
    PCB *best = NULL;

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == READY)
        {
            if(best == NULL ||
               pcb_table[i].priority < best->priority)
            {
                best = &pcb_table[i];
            }
        }
    }

    return best;
}

PCB* sjf_scheduler()
{
    PCB *best = NULL;

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == READY)
        {
            int remaining =
                pcb_table[i].program_size -
                pcb_table[i].cpu_time_used;

            if(best == NULL)
            {
                best = &pcb_table[i];
            }
            else
            {
                int best_remaining =
                    best->program_size -
                    best->cpu_time_used;

                if(remaining < best_remaining)
                {
                    best = &pcb_table[i];
                }
            }
        }
    }

    return best;
}

PCB* rm_scheduler()
{
    return priority_scheduler();
}

PCB* edf_scheduler()
{
    PCB *best = NULL;

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == READY)
        {
            if(best == NULL ||
               pcb_table[i].end_time < best->end_time)
            {
                best = &pcb_table[i];
            }
        }
    }

    return best;
}

void long_term_scheduler()
{
    if(is_empty(&blocked_queue))
    {
        printf("No blocked processes\n");
        return;
    }

    int pid = dequeue(&blocked_queue);

    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].pid == pid)
        {
            pcb_table[i].state = READY;

            printf("Process %d unblocked\n",
                   pid);

            return;
        }
    }
}

void interrupt_running_process(PCB *p)
{
    if(p == NULL)
    {
        return;
    }

    p->state = BLOCKED;

    enqueue(&blocked_queue, p->pid);

    printf("Process %d interrupted\n",
           p->pid);
}

void print_report()
{
    printf("==================== SYSTEM REPORT ====================\n");
    printf("Global Time: %d\n", global_time);
    printf("----------------------------------------------------\n");


    printf("RUNNING:\n");
    int found_running = 0;
    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == RUNNING) 
        {
            printf("  [PID=%d] PPID=%d | PC=%d | VAR=%d | PRIO=%d | CPU_USED=%d\n",
                   pcb_table[i].pid,
                   pcb_table[i].ppid,
                   pcb_table[i].pc,
                   pcb_table[i].variable,
                   pcb_table[i].priority,
                   pcb_table[i].cpu_time_used);
            found_running = 1;
        }
    }
    if(!found_running) printf("  (Sistema em IDLE)\n");


    printf("\nREADY QUEUE:\n");
    int found_ready = 0;
    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == READY)
        {

            printf("  [PID=%d] PPID=%d | PRIO=%d | VAR=%d | CPU_USED=%d\n",
                   pcb_table[i].pid,
                   pcb_table[i].ppid,
                   pcb_table[i].priority,
                   pcb_table[i].variable,
                   pcb_table[i].cpu_time_used);
            found_ready = 1;
        }
    }
    if(!found_ready) printf("  (Fila vazia)\n");


    printf("\nBLOCKED QUEUE:\n");
    int found_blocked = 0;
    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == BLOCKED)
        {
            printf("  [PID=%d] PPID=%d | VAR=%d | Aguardando comando D\n",
                   pcb_table[i].pid,
                   pcb_table[i].ppid,
                   pcb_table[i].variable);
            found_blocked = 1;
        }
    }
    if(!found_blocked) printf("  (Nenhum processo bloqueado)\n");


    printf("\nTERMINATED / STATISTICS:\n");
    int found_term = 0;
    for(int i = 0; i < process_count; i++)
    {
        if(pcb_table[i].state == TERMINATED)
        {
            int turnaround = pcb_table[i].end_time - pcb_table[i].start_time;
            printf("  [PID=%d] CPU_Total=%d | Turnaround=%d\n",
                   pcb_table[i].pid,
                   pcb_table[i].cpu_time_used,
                   turnaround);
            found_term = 1;
        }
    }
    if(!found_term) printf("  (Nenhum processo terminado)\n");

    printf("====================================================\n\n");
}

void print_final_statistics()
{
    printf("\nFINAL STATISTICS\n");

    for(int i = 0; i < process_count; i++)
    {
        printf("PID=%d STATE=%d CPU=%d\n",
               pcb_table[i].pid,
               pcb_table[i].state,
               pcb_table[i].cpu_time_used);
    }
}
