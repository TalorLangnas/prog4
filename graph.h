#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int dist; // for dijkstra's algorithm
    int visited; // for dijkstra's algorithm
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode head,int ver1,int ver2);
void TSP_cmd(pnode head);
pnode new_node(int vertex,pnode *head);
void new_edge(int myWeight,pnode source , pnode dest);
pnode find_vertex(int input, pnode head);
pnode setVertex(int numOfVertex);
void free_edges(pnode vertex);
void swap(int *numbers, int index1, int index2);
pnode MinV(pnode head);
void TSP_SIDE(pnode head, int *num, int k, int v, int *value);


#endif
