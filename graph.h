typedef struct Node {
    int vertex;
    struct node* next;
} Node;

typedef struct Graph {
    int vertices;
    Node** adjLists;
} Graph;

Node* createNode(int vertex);

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void fprintGraph(FILE* fp, Graph* graph);
int nodeDegree(Graph* graph, int vertex);