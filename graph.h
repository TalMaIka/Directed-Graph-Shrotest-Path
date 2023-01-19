#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head, int a, int b);
void TSP_cmd(pnode* head);
pnode createNode(int node_num);
pnode findNode(pnode* head,int num);
pedge createEdge(pnode dest, int weight);
void printGraph(pnode head);
void deleteEdge(pnode sourceNode);
void updateEdges(pnode *head);
#endif
