//
// Created by DELL on 27/05/2024.
//Prim Adja a un souci
// V est uniquement défini à 5 il faut le changer  en comme on veut

#ifndef TPRO_PRIMADJA_H
#define TPRO_PRIMADJA_H
#include <limits.h>
#include <stdbool.h>

#define V 9

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}
// fonction de génération du résultat
void generateDotFileForMatrixPrimMST(int parent[], int graph[V][V], const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "graph G {\n");
    for (int i = 1; i < V; i++) {
        fprintf(file, "    %d -- %d [label=%d];\n", parent[i], i, graph[i][parent[i]]);
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Fichier DOT pour Prim MST généré : %s\n", filename);
}



void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
    generateDotFileForMatrixPrimMST(parent, graph, "C:\\Users\\azang\\CLionProjects\\TPRO\\prim_mst_matrix.dot");
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX, mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}



// Fonction pour générer un fichier DOT pour la matrice d'adjacence
void generateDotFileForMatrix(int graph[V][V], const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "graph G {\n");
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                fprintf(file, "    %d -- %d [label=%d];\n", i, j, graph[i][j]);
            }
        }
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Fichier DOT du graphe originel a ete genere : %s\n", filename);
}
#endif //TPRO_PRIMADJA_H
