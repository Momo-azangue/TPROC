//
// Created by DELL on 27/05/2024.
//

#ifndef TPRO_DJISKTRALC_H
#define TPRO_DJISKTRALC_H

#include <limits.h>
#include <stdbool.h>

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

void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
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
            }
            temp = temp->next;
        }
    }

    printSolution(dist, V);
}
#endif //TPRO_DJISKTRALC_H
