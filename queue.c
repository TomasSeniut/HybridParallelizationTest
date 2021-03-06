//
// Created by tomas on 18.12.16.
//

#include <stddef.h>
#include <stdlib.h>
#include "queue.h"

typedef struct {
    struct stack_node *front;
    struct stack_node *rear;
} Queue;

static Queue *_queue;
static int _elementCount;

void initQueue()
{
    _queue = (Queue*)malloc(sizeof(Queue));
    _queue->front = _queue->rear = NULL;
}

void enQueue(stack_data data)
{
    _elementCount++;

    stack_node *tmp = (stack_node *) malloc(sizeof(stack_node));
    if (tmp == NULL) {
        exit(222);
    }
    tmp->data = data;

    if (_queue->rear == NULL)
    {
        _queue->front = _queue->rear = tmp;
        return;
    }

    _queue->rear->next = tmp;
    _queue->rear = tmp;
}

stack_data deQueue()
{
    _elementCount--;

    stack_node *tmp = _queue->front;
    stack_data node = _queue->front->data;

    free(tmp);

    _queue->front = _queue->front->next;

    if (_queue->front == NULL)
        _queue->rear = NULL;

    return node;
}

int queueSize()
{
    return _elementCount;
}

int isQueueEmpty()
{
    return _queue->front == NULL ? 1 : 0;
}