//
// Created by tomas on 19.1.5.
//

#include <stdio.h>
#include "malloc.h"
#include "IO.h"

data ReadData() {
    FILE *fp;
    fp = fopen("../data/data.txt", "r");

    int size;
    fscanf(fp, "%d\n", &size);

    data info;
    info.size = size;
    info.array = malloc(sizeof(int *) * info.size);

    for (int i = 0; i < size; ++i) {
        fscanf(fp, "%d\n", &info.array[i]);
    }

    fclose(fp);

    return info;
}