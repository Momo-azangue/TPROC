//
// Created by DELL on 27/05/2024.
//

#ifndef TPRO_KRUSKALLC_H
#define TPRO_KRUSKALLC_H
#include <stdio.h>
#include <stdlib.h>
// Structure pour représenter une arête
typedef struct {
    int src, dest, weight;
} Edge;

// Structure pour représenter un graphe
typedef struct {
    int V, E;
    Edge* edges;
} Graph;

// Structure pour les ensembles disjoints
typedef struct {
    int parent;
    int rank;
} Subset;

// Fonction pour créer un graphe
Graph* CreateGraph(int V, int E) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*) malloc(graph->E * sizeof(Edge));
    return graph;
}

// Trouver l'ensemble d'un élément i
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}


// Union de deux ensembles x et y (union par rang)
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Fonction de comparaison pour qsort
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*) a;
    Edge* edgeB = (Edge*) b;
    return edgeA->weight - edgeB->weight;
}

// Algorithme de Kruskal
void KruskalAlgo(Graph* graph) {
    int V = graph->V;
    Edge result[V]; // Ce sera notre MST
    int e = 0; // Indice utilisé pour result[]
    int i = 0; // Indice utilisé pour trier les arêtes

    // Étape 1 : Triez toutes les arêtes par ordre croissant de poids
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Allouez de la mémoire pour créer V sous-ensembles
    Subset* subsets = (Subset*) malloc(V * sizeof(Subset));

    // Créez V sous-ensembles avec des éléments uniques
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Nombre d'arêtes dans MST doit être égal à V-1
    while (e < V - 1 && i < graph->E) {
        // Étape 2 : Choisissez la plus petite arête. Incrémentez l'indice pour la prochaine itération
        Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Si l'inclusion de cette arête ne forme pas de cycle, l'inclure dans le résultat
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Afficher le contenu de result[] pour formater le MST
    printf("Les arêtes du MST sont:\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    free(subsets);
}

/***
 * Union-Find: Utilisé pour gérer les ensembles de sommets et vérifier s'ils sont connectés, aidant ainsi à détecter les cycles.
qsort: La fonction standard de C utilisée pour trier les arêtes en fonction de leur poids.
  ****/

// Fonction pour générer un fichier DOT
void generateDotFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "graph G {\n");
    for (int i = 0; i < graph->E; ++i) {
        fprintf(file, "    %d -- %d [label=%d];\n", graph->edges[i].src, graph->edges[i].dest, graph->edges[i].weight);
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Fichier DOT est genere  : %s\n", filename);
}

#endif //TPRO_KRUSKALLC_H
