#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

queue_t *init_queue(int capacity)
{
  queue_t *queue = malloc(sizeof(queue_t));
  if (queue == NULL) {
      return  NULL;
  }
  queue->capacity = capacity;
  queue->head = queue->tail = 0;
  queue->data = (int *)malloc(sizeof(int) * capacity);
  return queue;
}

static int next_head(queue_t *q)
{
  return (q->head + 1) % (q->capacity);
}

static int next_tail(queue_t *q)
{
  return (q->tail + 1) % (q->capacity);
}

int enque(queue_t *queue, int data)
{
  if (next_tail(queue) == queue->head) {
    return QUEUE_FULL;
  }
  queue->data[queue->tail] = data;
  queue->tail = next_tail(queue);
  return 0;
}

int deque(queue_t *queue, int *data)
{
  if (data == NULL) {
    return NULL_ARGUMENT;
  }
  if (queue->head == queue->tail) {
    return QUEUE_EMPTY;
  }
  int retval = queue->data[queue->head];
  queue->head = next_head(queue);
  return retval;
}
