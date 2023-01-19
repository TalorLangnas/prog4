#include "graph.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


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
    while (head)
    {
        if (head->node_num == input)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}


pnode setVertex(int numOfVertex){ //Create graph Vertex
    pnode curr = (pnode)malloc(sizeof(node));
    if (!curr)
    {
        return NULL;
    }
    curr->node_num = numOfVertex - 1;
    curr->edges = NULL;
    curr->next = NULL;

    for (int i = 1; i < numOfVertex; i++)
    {
        pnode newNode = (pnode)malloc(sizeof(node));
        if (!newNode)
        {
            return NULL;
        }
        newNode->node_num = numOfVertex - i - 1;
        newNode->edges = NULL;
        newNode->next = curr;
        curr = newNode;
    }
    return curr;
}




void build_graph_cmd(pnode *head){ //for option A
    deleteGraph_cmd(head);
    int number_ver=0;
    int source_v=0;
    int dest_v=0;
    int weight=0;
    char c;
    int check =0;
    pnode sourceVertex=NULL;
    pnode destVertex=NULL;
    scanf("%d", &number_ver);
    *head = setVertex(number_ver);
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
                
        while(!feof(stdin) && (check=scanf("%d", &dest_v))){
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

void delete_edge(pnode item, int endpoint){
    pedge currEdge = item->edges;
    pedge prevEdge = NULL;
    while (currEdge) {
        if(currEdge->endpoint->node_num == endpoint){
            if(prevEdge == NULL) {
                item->edges = currEdge->next;
            } else {
                prevEdge->next = currEdge->next;
            }
            free(currEdge);
            break;
        }
        prevEdge = currEdge;
        currEdge = currEdge->next;
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

void deleteGraph_cmd(pnode *head)
{
    pnode temp = *head;
    pedge curredge = NULL;
    pnode tmp2 = NULL;
    while (temp)
    {
        curredge = temp->edges;
        while (curredge)
        {
            pedge tmp3 = curredge;
            curredge = curredge->next;
            free(tmp3);
        }
        tmp2 = temp;
        temp = temp->next;
        free(tmp2);
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
pnode MinV(pnode head){
    pnode current = head, min = NULL;
    int mind = __INT_MAX__;
    while (current) {
        if (!current->visited && current->dist < mind) {
            min = current;
            mind = current->dist;
        }
        current = current->next;
    }
    return min;
}


int shortsPath_cmd(pnode head, int ver1, int ver2)
{
    pnode ver1N = NULL;
    pnode ver2N = NULL;
    pnode current = head;

    while (current)
    {
        current->dist = __INT_MAX__;
        current->visited = 0;
        if (current->node_num == ver1)
        {
            ver1N = current;
            ver1N->dist = 0;
        }
        else if (current->node_num == ver2)
        {
            ver1N = current;
        }
        current = current->next;
    }

    current = MinV(head);
    while (current)
    {
        current->visited = 1;
        pedge cedge = current->edges;
        while (cedge)
        {
            if (!cedge->endpoint->visited && current->dist + cedge->weight < cedge->endpoint->dist)
            {
                cedge->endpoint->dist = current->dist + cedge->weight;
            }
            cedge = cedge->next;
        }
        current = MinV(head);
    }
    if (ver2N->dist == __INT_MAX__)
    {
        ver2N->dist = -1;
    }
    return ver2N->dist;
}
void swap(int *numbers, int index1, int index2)
{
    int temp = numbers[index1];
    numbers[index1] = numbers[index2];
    numbers[index2] = temp;
}
void TSP_SIDE(pnode head, int *num, int k, int v, int *value)
{
    if (k == 2)
    {
        int d = shortsPath_cmd(head, num[0], num[1]);
        if (d != -1 && (v + d) < *value)
        {
            *value = (v + d);
        }
        return;
    }

    for (int i = 1; i < k; i++)
    {
        swap(num, 1, i);
        int d = shortsPath_cmd(head, num[0], num[1]);
        if (d == -1)
        {
            return;
        }
        TSP_SIDE(head, num + 1, k - 1, v + d, value);
        swap(num, i, 1);
    }
}

void TSP_cmd(pnode head)
{
    int k;
    scanf("%d", &k);
    int *numbers = (int *)(malloc(sizeof(int) * k));
    int value = __INT_MAX__;
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &numbers[i]);
    }

    for (int i = 0; i < k; i++)
    {
        swap(numbers, 0, i);
        TSP_SIDE(head, numbers, k, 0, &value);
        swap(numbers, i, 0);
    }

    if (value == __INT_MAX__)
    {
        value = -1;
    }
    free(numbers);
    printf("TSP shortest path: %d \n", value);
}
