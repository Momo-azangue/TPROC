#include <stdio.h>
#include <stdlib.h>
#include "kruskalLc.h"
#include "PrimAdja.h"
int main() {

    int graph[V][V] = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0},
    };

    primMST(graph);


    return 0;
}
