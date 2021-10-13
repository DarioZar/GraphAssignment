typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    Node** adjLists;
} Graph;

Node* createNode(int vertex);

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void addEdge_dir(Graph* graph, int src, int dest);
void removeEdge(Graph* graph, int src, int dest);
void removeEdge_dir(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void fprintGraph(FILE* fp, Graph* graph);
int nodeDegree(Graph* graph, int vertex);
int** toAdjMatrix(Graph* graph);
