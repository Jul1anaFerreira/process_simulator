#ifndef SCHEDULER_H
#define SCHEDULER_H

#define QUEUE_SIZE 50

typedef struct {
    int items[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q);

int is_empty(Queue *q);

void enqueue(Queue *q, int value);

int dequeue(Queue *q);

#endif