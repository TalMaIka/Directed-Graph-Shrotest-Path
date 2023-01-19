#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    char op;
    pnode head = NULL;
    while(!feof(stdin)){
        if(op != 'A'){
            scanf("%c",&op);
        }
        if(op == 'A'){
            op = build_graph_cmd(&head);
        }
        if(op == 'B'){
            updateEdges(&head);
        }
        if(op == 'D'){
            delete_node_cmd(&head);
        }
        if(op == 'S'){
            int a,b;
            scanf("%d %d",&a,&b);
            shortsPath_cmd(head,a,b);
        }
        if(op == 'T'){
           //Unfortunately we didn't made TSP method right, after spending hours and days on it. 
        }
  // printGraph(head);
}
}
