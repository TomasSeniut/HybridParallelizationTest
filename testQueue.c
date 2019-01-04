//
// Created by tomas on 18.12.16.
//

#include <stdio.h>
#include "queue.h"

int testQueue()
{
    initQueue();

    stack_data data1;
    data1.someValue = 8;
    enQueue(data1);

    stack_data data2;
    data2.someValue = 2;
    enQueue(data2);

    stack_data data3;
    data3.someValue = 11;
    enQueue(data3);

    printf("size: %d\n", queueSize());

    stack_data dedata1 = deQueue();
    printf("%d\n", dedata1.someValue);

    printf("size: %d\n", queueSize());

    stack_data dedata2 = deQueue();
    printf("%d\n", dedata2.someValue);

    printf("size: %d\n", queueSize());

    stack_data data4;
    data4.someValue = 100;
    enQueue(data4);

    printf("size: %d\n", queueSize());

    stack_data dedata3 = deQueue();
    printf("%d\n", dedata3.someValue);

    printf("size: %d\n", queueSize());

    stack_data dedata4 = deQueue();
    printf("%d\n", dedata4.someValue);

    printf("size: %d\n", queueSize());
}