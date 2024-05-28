//
// Created by DELL on 27/05/2024.
//

#ifndef TPRO_PRIMLC_H
#define TPRO_PRIMLC_H
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
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

int minKey(int key[], bool mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int V, Graph* graph) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        Node* temp = graph->array[i].head;
        while (temp) {
            if (temp->dest == parent[i]) {
                printf("%d - %d \t%d \n", parent[i], i, temp->weight);
                break;
            }
            temp = temp->next;
        }
    }
}


void generateDotFileForPrimMST(int parent[], int V, Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "graph G {\n");
    for (int i = 1; i < V; ++i) {
        Node* temp = graph->array[i].head;
        while (temp) {
            if (temp->dest == parent[i]) {
                fprintf(file, "    %d -- %d [label=%d];\n", parent[i], i, temp->weight);
                break;
            }
            temp = temp->next;
        }
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Fichier DOT pour Prim MST généré : %s\n", filename);
}


void primMST(Graph* graph) {
    int V = graph->V;
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX, mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            if (mstSet[v] == false && temp->weight < key[v]) {
                parent[v] = u, key[v] = temp->weight;
            }
            temp = temp->next;
        }
    }

    printMST(parent, V, graph);
    generateDotFileForPrimMST(parent, V, graph, "C:\\Users\\azang\\CLionProjects\\TPRO\\prim_liste.dot");
}

#endif //TPRO_PRIMLC_H
