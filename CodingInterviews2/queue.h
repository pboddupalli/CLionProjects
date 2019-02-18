#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_FULL -1
#define QUEUE_EMPTY -2
#define NULL_ARGUMENT -3

struct queue
{
    int head;
    int tail;
    int capacity;
    int *data;
};

typedef struct queue queue_t;

extern queue_t *init_queue(int capacity);

extern int enque(queue_t *queue, int data);

extern int deque(queue_t *queue, int *data);

#endif

