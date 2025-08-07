/*
 * File Name: searchAlgorithm.h
 * Author: Haylee Jackson
 * Purpose: header file for searchAlgorithm.c
 * Last Modified: 06/08/2025
*/

#ifndef SEARCH_H
#define SEARCH_H

#include "map.h"

#define MAX_NODES 1000
#define MAX_SUCCESSORS 4

typedef struct {
    int col, row;
} Point;

/* Structure to represent a node in the search tree */
typedef struct Node {
    /* Position of the node in the grid */
    Point pos;
    /* Cost from the start node to this node */
    int g;
    /* Heuristic cost from this node to the goal node */
    int h;
    /* Total cost (g + h) */
    int f;
    /* Pointer to the parent node */
    struct Node* parent;
} Node;

/* Structure to represent a list of nodes (either open or closed) */
typedef struct {
    /* Array of node pointers */
    Node* nodes[MAX_NODES];
    /* Current size of the list */
    int size;
} List;

Point* aStar(char ** map, Point start, Point goal);

#endif
