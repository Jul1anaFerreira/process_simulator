#ifndef SCHEDULER_H
#define SCHEDULER_H

#define QUEUE_SIZE 50

#include "process.h"

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q);

int is_empty(Queue *q);

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

PCB* fcfs_scheduler();

PCB* priority_scheduler();

PCB* sjf_scheduler();

PCB* rm_scheduler();

PCB* edf_scheduler();

void long_term_scheduler();

void interrupt_running_process(PCB *p);

void print_report();

void print_final_statistics();

#endif
