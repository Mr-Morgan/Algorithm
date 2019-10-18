
﻿#include <stdio.h>
#include <stdlib.h>

/*
    1. Написать функцию обхода графа в глубину.
    2. Написать рекурсивную функцию обхода графа в ширину.
*/

#define T int

typedef int boolean;
#define true 1
#define false 0

typedef struct List List;

typedef struct GraphNode {
    T data;
    boolean used;
    List *edge;
} GraphNode;

/*********************** List *****************************/
typedef struct List{
    GraphNode **nodes;
    int size;
} List;

void initList(List *ls)
{
    ls->nodes = NULL;
    ls->size = 0;
}//void initList(List *ls)

void cpNodes(List *ls, List *n_ls)
{
    if(ls->nodes)
        for (int i = 0; i < ls->size; ++i)
            n_ls->nodes[i] = ls->nodes[i];
}//void cpList(List *ls, List *n_ls)

List* reallocList(List *ls)
{
    List *new_ls = (List*)malloc(sizeof(List));
    initList(new_ls);
    new_ls->nodes = (GraphNode**)calloc((ls->size+1), sizeof(GraphNode*));
    new_ls->size = ls->size + 1;
    return new_ls;
}//List* reallocList(List *ls)

List* addNode(List *ls, GraphNode *value)
{
    List* temp = reallocList(ls);
    cpNodes(ls, temp);
    *(temp->nodes + (temp->size - 1)) = value;
    free(ls);
    return temp;
}//void push(List *ls, GraphNode *value)
/********************** endList ***************************/

/*********************** Ex. 1 ****************************/
#define H 7
#define W 7
T graph[H][W] = {  {0, 3, 2, 5, 6, 8, 7},
                   {3, 0, 1, 0, 1, 0, 0},
                   {2, 1, 0, 1, 0, 1, 1},
                   {5, 0, 1, 0, 0, 1, 1},
                   {6, 1, 0, 0, 0, 0, 0},
                   {8, 0, 1, 1, 0, 0, 0},
                   {7, 0, 1, 1, 0, 0, 0}
                };

GraphNode* fillingGraph()
{
    GraphNode *tmp = (GraphNode*)calloc((unsigned)H-1, sizeof(GraphNode));

    for (int h = 0; h < H-1; ++h) {
        tmp[h].edge = (List*)malloc(sizeof(List));
        initList(tmp[h].edge);
        for (int w = h; w < W; ++w)
            if(!h && w) tmp[w-1].data = graph[h][w];
            else if(graph[h][w]) tmp[h-1].edge = addNode(tmp[h-1].edge, tmp+w-1);
    }//for (int h = 1; h < H; ++h)
    return tmp;
}//GraphNode* fillingGraph(T *arr)

int main()
{
    printf("********************** Ex. 1 ***************************\n\n");
        GraphNode *head = fillingGraph();
    printf("\n\n");

    return 0;
}//int main()
