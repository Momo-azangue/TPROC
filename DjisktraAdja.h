//
// Created by DELL on 27/05/2024.
//

#ifndef TPRO_DJISKTRAADJA_H
#define TPRO_DJISKTRAADJA_H
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#define  V 9

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int n) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void generateDotFileForDijkstraAdjacency(int parent[], int dist[], int K, int graph[V][V], const char* filename) {
FILE* file = fopen(filename, "w");
if (file == NULL) {
printf("Erreur d'ouverture du fichier.\n");
return;
}

fprintf(file, "digraph G {\n");
for (int i = 0; i < V; ++i) {
if (parent[i] != -1) {
fprintf(file, "    %d -> %d [label=%d];\n", parent[i], i, graph[parent[i]][i]);
}
}
fprintf(file, "}\n");

fclose(file);
printf("Fichier DOT pour Dijkstra généré : %s\n", filename);
}


void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, V);
    generateDotFileForDijkstraAdjacency(parent, dist, V, graph, "C:\\Users\\azang\\CLionProjects\\TPRO\\Dot\\dijkstra_adjacency.dot");
}
#endif //TPRO_DJISKTRAADJA_H
