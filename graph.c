#include "graph.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>


pnode new_node(int vertex,pnode *head){     //Create new node
    pnode p = (pnode)malloc(sizeof(node));
    if(!p){
        printf("memory allocation error\n");
    }
    p -> node_num = vertex;
    p -> next =  (*head);
    p -> edges = NULL;    
    *head = p;
    return p;
}

void new_edge(int myWeight,pnode source , pnode dest){
    pedge pEdge = (pedge)malloc(sizeof(edge));
    if(!pEdge){
        printf("allocate is NULL");
        return;
    }
    pEdge -> weight = myWeight;
    pEdge->endpoint = dest;
    pEdge->next = source->edges;
    source->edges = pEdge;    
}

pnode find_vertex(int input, pnode head){
    pnode tmp = head;
    while(tmp){
          if(tmp->next == input){
            return tmp;
          } 
    }    
    return NULL;
}


pnode setVertex(int numOfVertex){ //Create graph Vertex
    pnode head = NULL;
    pnode tmp = new_node(numOfVertex-1, head);
    for (int i = 1; i < numOfVertex; i++)
    {
        tmp = new_node(numOfVertex-i-1, head);
    }
    return head;
}




void build_graph_cmd(pnode *head){ //for option A
    int number_ver;
    int source_v;
    int dest_v;
    int weight;
    char c ;
    int check =0;
    pnode head=NULL;
    pnode sourceVertex=NULL;
    pnode destVertex=NULL;
    pedge Pedge = NULL;


    scanf("%d", &number_ver);
    head = setVertex(number_ver);
    if(!head){
        printf("head is null");
        return;
    }
    
    for(int i=0; i<number_ver;i++){
        scanf(" %c", &c);
        scanf("%d", &source_v);
        sourceVertex = find_vertex(source_v,*head);
        if(!sourceVertex){
            return;
        }
                
    while(!feof(stdin) && (check=scanf("%d", dest_v))){
        destVertex = find_vertex(dest_v,*head);
        scanf("%d",&weight);
        
       new_edge(weight,sourceVertex, destVertex);
    }
    }    

} 

void free_edges(pnode vertex){
    pedge currEdge = vertex->edges;
    while (currEdge)
    {
        pedge temp = currEdge;
        currEdge = currEdge->next;
        free(temp);
    }
    vertex->edges = NULL;
}

void insert_node_cmd(pnode *head){ //for option B
    pnode newVertex = NULL;
    pnode destVertex = NULL;
    int input;
    int dest_v;
    int weight;
    int check;

    scanf("%d",&input);
    newVertex = find_vertex(input, *head);
    if(newVertex!=NULL){
        free_edges(newVertex);
    }

    else{
        newVertex = new_node(input, head);
    }

    while((!feof(stdin)) && (check = scanf("%d", &dest_v))){
        scanf("%d", &weight);
        destVertex = find_vertex(dest_v,*head);        
        new_edge(weight,newVertex, destVertex);
    }    

}


void delete_node_cmd(pnode *head){ //option D
    int ver;
    pnode curr = *head;
    pnode prev = NULL;
    scanf("%d", &ver);
    while (curr) {
        delete_edge(curr, ver);
        curr = curr->next;
    }
    curr = *head;
    while (curr) {
        if(curr->node_num == ver){
            if(prev == NULL){
                *head = curr->next;
            } else{
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}


int shortsPath_cmd(pnode head){
    int sourceNodeNum;
    int desNode;
    scanf("%d", &sourceNodeNum);
    scanf("%d", &desNode);

    pnode sourceNode = NULL;
    pnode destNode = NULL;
    pnode currNode = head;

    // finding both vertices and resetting values
    while (currNode)
    {
        currNode->dist = __INT_MAX__;
        currNode->visited = 0;
        if (currNode->node_num == sourceNodeNum)
        {
            sourceNode = currNode;
            sourceNode->dist = 0;
        }
        else if (currNode->node_num == desNode)
        {
            destNode = currNode;
        }
        currNode = currNode->next;
    }

    // running dijkstra's algorithm
    currNode = findMinNotVisited(head);
    while (currNode)
    {
        currNode->visited = 1;
        pedge currentEdge = currNode->edges;
        while (currentEdge)
        {
            if (!currentEdge->endpoint->visited && currNode->dist + currentEdge->weight < currentEdge->endpoint->dist)
            {
                currentEdge->endpoint->dist = currNode->dist + currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
        currNode = findMinNotVisited(head);
    }
    if (destNode->dist == __INT_MAX__)
    {
        destNode->dist = -1;
    }
    return destNode->dist;
}

pnode findMinNotVisited(pnode head)
{
    int minNodeIndex = __INT_MAX__;
    pnode result = NULL;
    while (head)
    {
        if (!head->visited && head->dist < minNodeIndex)
        {
            minNodeIndex = head->dist;
            result = head;
        }
        head = head->next;
    }
    return result;
}

void TSP_cmd(pnode head){
    int numberNodes = 0;
    scanf("%d", &numberNodes);
    int WhichNodes[numberNodes];

    for (int i = 0; i < numberNodes; ++i) 
    {
        scanf("%d", &WhichNodes[i]);
    }

    int f = factorial(numberNodes);
    int permutations[f];
    int temp = 0;
    per(head,WhichNodes,0,numberNodes-1,permutations,&temp);
    int n = min(permutations,f);
    
    if(permutations[n] == __INT_MAX__)
    {
        printf("TSP shortest path: %d \n",-1);
    }
    else
    {
        printf("TSP shortest path: %d \n",permutations[n]);
    }
}

void printGraph_cmd(pnode head)
{
    if (head == NULL)
    {
        printf("NO GRAPH\n");
    }
    pnode temp = head;
    pedge edge1;
    while (temp)
    {
        edge1 = temp->edges;
        printf("Edges of %d:\n", temp->node_num);
        while (edge1)
        {
            printf("V:%d, E:%d W:%d\n", temp->node_num, edge1->endpoint->node_num, edge1->weight);
            edge1 = edge1->next;
        }
        temp = temp->next;
    }
}

void swap(int *x, int *y) 
{
    int c;
    c = *x;
    *x = *y;
    *y = c;
}

int factorial(int size)
{
    if(size < 0) return 0;
    if(size == 0) return 1;
    return factorial(size-1)*size;
}

int min(const int arr[],int n)
{
    int index = 0;

    for (int i = 1; i <n; ++i) 
    {
        if(arr[i]<arr[index]){index = i;}
    }

    return index;
}

int FindShortestPath(node **head, int values[], int len)
{
    int dst = 0;
    for (int i = 0; i < len-1; ++i) {
        int dijk = dijkstra(head,values[i],values[i+1],0);
        if(dijk == __INT_MAX__){
            return __INT_MAX__;
        }
        dst += dijk;
    }
    return dst;
}



void per(node **head, int *values, int right, int left ,int *permutat, int *n)
{
    if(right == left)
    {
        permutat[(*n)++] = FindShortestPath(head, values, left+1);
        return;
    }

    for (int i = right; i <=left; ++i) 
    {
        swap((values + i), (values + right));
        per(head,values,right+1,left,permutat,n);
        swap((values+i),(values+right));
    }
}