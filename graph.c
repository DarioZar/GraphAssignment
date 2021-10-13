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

void addEdge_dir(Graph* graph, int src, int dest) {
    // Create [dest] node, then push node at the head of list[src]
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void removeEdge_dir(Graph* graph, int src, int dest) {
    Node* temp = graph->adjLists[src];
    Node* prev;

    // if it's the head node, push list to the right
    // else search dest node and delete it, connecting prev and next nodes
    if(temp!=NULL && temp->vertex==dest) {
        graph->adjLists[src] = temp->next;
    }
    else{
        while(temp!=NULL && temp->vertex!=dest) {
            prev = temp;
            temp = temp->next;
        }
        if(temp) prev->next = temp->next;
    }
    free(temp);
}

void addEdge(Graph* graph, int src, int dest) {
    addEdge_dir(graph, src, dest);
    addEdge_dir(graph, dest, src);
}

void removeEdge(Graph* graph, int src, int dest) {
    removeEdge_dir(graph, src, dest);
    removeEdge_dir(graph, dest, src);
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

void printGraph(Graph* graph) {
    fprintGraph(stdout, graph);
}