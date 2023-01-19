#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

pedge FindEdge(pnode source, pnode dest)
{
    pedge temp_edge = source->edges;
    while (temp_edge)
    {
        if (temp_edge->endpoint == dest)
        {
            return temp_edge;
        }
        temp_edge = temp_edge->next;
    }
    return NULL;
}

void deleteEdge(pnode sourceNode)
{
    if (sourceNode != NULL)
    {
        pedge temp_edge = sourceNode->edges;
        while (temp_edge)
        {
            pedge next_edge = temp_edge->next;
            free(temp_edge);
            temp_edge = next_edge;
        }
        sourceNode->edges = NULL;
    }
}

void updateEdges(pnode *head)
{
    int source;
    scanf("%d", &source);
    pnode sourceNode = findNode(head, source);
    if (sourceNode != NULL)
    {
        deleteEdge(sourceNode);
    }
    else
    {
        sourceNode = createNode(source);
        pnode temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = sourceNode;
    }
    int dest, weight;
    int a;
    while ((a = scanf("%d %d", &dest, &weight)) == 2)
    {
        pnode destNode = findNode(head, dest);
        pedge existing_edge = FindEdge(sourceNode, destNode);
        if (existing_edge != NULL)
        {
            existing_edge->weight = weight;
        }
        else
        {
            pedge newEdge = createEdge(destNode, weight);
            if (sourceNode->edges == NULL)
                sourceNode->edges = newEdge;
            else
            {
                pedge tempEdge = sourceNode->edges;
                while (tempEdge->next != NULL)
                {
                    tempEdge = tempEdge->next;
                }
                tempEdge->next = newEdge;
            }
        }
    }
}

// Deletes the graph by freeing every malloc made in the proccess.
void deleteGraph_cmd(pnode *head)
{
    pnode temp = *head;
    while (temp)
    {
        pedge temp_edge = temp->edges;
        while (temp_edge)
        {
            pedge next_edge = temp_edge->next;
            free(temp_edge);
            temp_edge = next_edge;
        }
        pnode next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    *head = NULL;
}

// Node constractor.
pnode createNode(int node_num)
{
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = node_num;
    new_node->edges = NULL;
    new_node->next = NULL;
    return new_node;
}

// Node finder.
pnode findNode(pnode *head, int num)
{
    if (head == NULL)
    {
        return NULL;
    }
    pnode temp = *head;
    while (temp != NULL)
    {
        if (temp->node_num == num)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void printGraph(pnode head)
{
    pnode temp = head;
    while (temp != NULL)
    {
        printf("Node %d:  ", temp->node_num);
        pedge temp_edge = temp->edges;
        while (temp_edge)
        {
            printf("%d---%d--->%d    ", temp->node_num, temp_edge->weight, temp_edge->endpoint->node_num);
            temp_edge = temp_edge->next;
        }
        printf("\n");
        temp = temp->next;
    }
}

pedge createEdge(pnode dest, int weight)
{
    pedge new_edge = (pedge)malloc(sizeof(edge));
    new_edge->weight = weight;
    new_edge->endpoint = dest;
    new_edge->next = NULL;
    return new_edge;
}

void insert_node_cmd(pnode *head)
{
    int source;
    scanf("%d", &source);
    pnode sourceNode = findNode(head, source);
    if (sourceNode == NULL)
    {
        sourceNode = createNode(source);
    }
    int dest, weight;
    int a;
    while ((a = scanf("%d %d", &dest, &weight)) == 2)
    {
        pnode destNode = findNode(head, dest);
        pedge existing_edge = FindEdge(sourceNode, destNode);
        if (existing_edge != NULL)
        {
            existing_edge->weight = weight;
        }
        else
        {
            pedge newEdge = createEdge(destNode, weight);
            if (sourceNode->edges == NULL)
                sourceNode->edges = newEdge;
            else
            {
                pedge tempEdge = sourceNode->edges;
                while (tempEdge->next != NULL)
                {
                    tempEdge = tempEdge->next;
                }
                tempEdge->next = newEdge;
            }
        }
    }
}

char build_graph_cmd(pnode *head)
{
    // Removes a prev graph if exists.
    if (*head != NULL)
    {
        deleteGraph_cmd(head);
    }
    int num_nodes;
    scanf("%d", &num_nodes);
    for (int i = 0; i < num_nodes; i++)
    {
        pnode newNode = createNode(i);
        if (i == 0)
        {
            *head = newNode;
        }
        if (i >= 1)
        {
            pnode temp = *head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    char c;
    scanf(" %c ", &c);
    while (c == 'n')
    {
        insert_node_cmd(head);
        c = '\0';
        scanf(" %c ", &c);
    }
    return c;
}

void delete_node_cmd(pnode *head)
{
    int source;
    scanf("%d", &source);
    pnode nodeToDelete = findNode(head, source);
    if (nodeToDelete != NULL)
    {
        // remove edges pointing to this node
        pnode temp = *head;
        while (temp != NULL)
        {
            pedge edgeToDelete = FindEdge(temp, nodeToDelete);
            if (edgeToDelete != NULL)
            {
                // remove the edge
                if (temp->edges == edgeToDelete)
                {
                    temp->edges = edgeToDelete->next;
                }
                else
                {
                    pedge prevEdge = temp->edges;
                    while (prevEdge->next != edgeToDelete)
                    {
                        prevEdge = prevEdge->next;
                    }
                    prevEdge->next = edgeToDelete->next;
                }
                free(edgeToDelete);
            }
            temp = temp->next;
        }

        // remove the node
        if (*head == nodeToDelete)
        {
            *head = nodeToDelete->next;
        }
        else
        {
            pnode prevNode = *head;
            while (prevNode->next != nodeToDelete)
            {
                prevNode = prevNode->next;
            }
            prevNode->next = nodeToDelete->next;
        }
        free(nodeToDelete);
    }
}

void shortsPath_cmd(pnode head, int source, int dest)
{
    pnode startNode = findNode(&head, source);
    pnode endNode = findNode(&head, dest);
    if (startNode == NULL || endNode == NULL)
    {
        printf("Invalid start or end node\n");
        return;
    }

    int dist[100];               
    int prev[100];               
    int visited[100] = {0};      
    int heap[100], heapSize = 0; 

    
    for (pnode curr = head; curr != NULL; curr = curr->next)
    {
        dist[curr->node_num] = INT_MAX;
        prev[curr->node_num] = -1;
        visited[curr->node_num] = 0;
        heap[heapSize++] = curr->node_num;
    }

    dist[startNode->node_num] = 0;

    while (heapSize > 0)
    {
        
        int curr = heap[0], currIndex = 0;
        for (int i = 1; i < heapSize; i++)
        {
            if (dist[heap[i]] < dist[curr])
            {
                curr = heap[i];
                currIndex = i;
            }
        }
        // remove the node from the heap
        heap[currIndex] = heap[--heapSize];

        if (visited[curr])
            continue;
        visited[curr] = 1;

        for (pedge edge = findNode(&head, curr)->edges; edge != NULL; edge = edge->next)
        {
            pnode neighbor = edge->endpoint;
            if (!visited[neighbor->node_num])
            {
                int newDist = dist[curr] + edge->weight;
                if (newDist < dist[neighbor->node_num])
                {
                    dist[neighbor->node_num] = newDist;
                    prev[neighbor->node_num] = curr;
                }
            }
        }

        // check if we have reached the end node
        if (curr == endNode->node_num)
        {
            if (dist[endNode->node_num] == INT_MAX)
            {
                dist[endNode->node_num] = -1;
            }
            printf("Dijsktra shortest path: %d\n", dist[endNode->node_num]);
        
            int currNode = endNode->node_num;
            while (currNode != -1)
            {
                currNode = prev[currNode];
            }
            break;
        }
    }
}

//Unfortunately we didn't made TSP method right, after spending hours and days on it. 