//
// Created by tomas on 18.12.16.
//

#ifndef HYBRIDPARALLELIZATION_QUEUE_H
#define HYBRIDPARALLELIZATION_QUEUE_H

typedef struct {
    int someValue;
} stack_data;

typedef struct stack_node stack_node;
struct stack_node
{
    stack_data data;
    stack_node* next;
};

void initQueue();
void enQueue(stack_data data);
stack_data deQueue();
int queueSize();
int isQueueEmpty();

#endif //HYBRIDPARALLELIZATION_QUEUE_H
