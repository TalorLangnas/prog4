#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    int mindistance = 0;
    char c = 0;
    pnode head = NULL;

    while (!feof(stdin))
    {
        switch (c)
        {
        case 'A':
            // printf("A:\n");
            build_graph_cmd(&head);
            break;
        case 'B':
            // printf("B:\n");
            insert_node_cmd(&head);
            break;
        case 'D':
            delete_node_cmd(&head);
            break;
        case 'S':
           int ver1 =0;
           int ver2 =0;
           scanf("%d",&ver1);
           scanf("%d",&ver2);
            mindistance = shortsPath_cmd(head,ver1,ver2);
            printf("Dijsktra shortest path: %d \n", mindistance);
            break;
        // case 'P':
        //     // printf("P:\n");
        //     printGraph_cmd(head);
        //     break;
        case 'T':
            TSP_cmd(head);
            break;
        // case 'Z':
        //     // printf("Z:\n");
        //     deleteGraph_cmd(&head);
        //     printGraph_cmd(head);
        //     break;
        default:
            break;
        }
        scanf(" %c", &c);
    }
    deleteGraph_cmd(&head);
    return 0;
}