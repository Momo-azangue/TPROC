//
// Created by DELL on 27/05/2024.
//

#ifndef TPRO_DJISKTRALC_H
#define TPRO_DJISKTRALC_H



#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct AdjList {
    Node* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

int minDistance(int dist[], bool sptSet[], int V) {
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

void generateDotFileForDijkstra(int parent[], int dist[], int V, Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "digraph G {\n");
    for (int i = 0; i < V; ++i) {
        if (parent[i] != -1) {
            fprintf(file, "    %d -> %d [label=%d];\n", parent[i], i, dist[i]);
        }
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Fichier DOT pour Dijkstra généré : %s\n", filename);
}

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
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
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printSolution(dist, V);
    generateDotFileForDijkstra(parent, dist, V, graph, "C:\\Users\\azang\\CLionProjects\\TPRO\\Dot\\dijkstra.dot");
}


#endif //TPRO_DJISKTRALC_H
