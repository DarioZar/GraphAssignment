#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

Node* createNode(int vertex) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjLists = (Node**) calloc(vertices, sizeof(Node*));

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int nodeDegree(Graph* graph, int vertex) {
    int deg=0;
    Node* node = graph->adjLists[vertex];
    while(node!=NULL) {
        deg++;
        node = node->next;
    }
    return deg;
}

int** toAdjMatrix(Graph* graph) {
    int i;
    int size = graph->vertices;
    Node* temp;
    int** adjMatrix = calloc(size, sizeof(int*));
    for(i=0;i<size;i++) {
        adjMatrix[i] = calloc(size, sizeof(int));
    }
    for(i=0;i<size;i++) {
        temp = graph->adjLists[i];
        while(temp) {
            adjMatrix[i][temp->vertex]+=1;
            temp = temp->next;
        }
    }
    return adjMatrix;
}

void printGraph(Graph* graph) {
    int i;
    for(i=0; i<graph->vertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("\nAdjacency list of vertex %d\n", i);
        while(temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void fprintGraph(FILE* fp, Graph* graph) {
    int i;
    for(i=0; i<graph->vertices; i++) {
        Node* temp = graph->adjLists[i];
        fprintf(fp, "\nAdjacency list of vertex %d\n", i);
        while(temp) {
            fprintf(fp, "%d -> ", temp->vertex);
            temp = temp->next;
        }
        fprintf(fp, "\n");
    }
}