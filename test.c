#include<stdio.h>
#include<stdlib.h>

#include "graph.h"

int main() {
    int i,j;
    Graph* graph = createGraph(5);
    addEdge(graph, 1, 2);
    addEdge(graph, 3, 4);
    addEdge_dir(graph, 1, 2);
    addEdge_dir(graph, 1, 3);
    addEdge_dir(graph, 4, 1);
    removeEdge_dir(graph, 4, 1);
    removeEdge_dir(graph, 2, 3);
    removeEdge(graph, 3, 4);

    printf("Grafo creato\n");
    int** adjMatrix = toAdjMatrix(graph);
    printf("adjMatrix creata\n");
    for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            printf("%d", adjMatrix[i][j]);
        }
        printf("\n");
    }

    printGraph(graph);

    return 0;
}