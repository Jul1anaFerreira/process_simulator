#include <stdio.h>

#include "../include/scheduler.h"

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