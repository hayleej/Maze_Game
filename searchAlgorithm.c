/*
 * File Name: searchAlgorithm.c
 * Author: Haylee Jackson
 * Purpose: A* Search functions for enemy movement
 * Last Modified: 06/08/2025
*/


#include "searchAlgorithm.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Function to create a new node*/
Node* createNode(Point pos, Node* parent, int g, int h)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->pos = pos;
    node->parent = parent;
    node->g = g;
    node->h = h;
    node->f = g + h;
    return node;
}

/* Function to add a node to a list*/
void addToList(List* list, Node* node)
{
    list->nodes[list->size++] = node;
}

/* Function to get the node with the lowest 'f' value from a list*/
Node* getLowestF(List* list)
{
    int lowestIndex = 0;
    int i = 1;
    for (i = 1; i < list->size; i++) {
        if (list->nodes[i]->f
            < list->nodes[lowestIndex]->f) {
            lowestIndex = i;
        }
    }
    Node* node = list->nodes[lowestIndex];
    list->nodes[lowestIndex] = list->nodes[--list->size];
    return node;
}

/* Function to check if a point is in a list*/
bool isInList(List* list, Point pos)
{
    int i = 0;
    for (i = 0; i < list->size; i++) {
        if (list->nodes[i]->pos.col == pos.col
            && list->nodes[i]->pos.row == pos.row) {
            return true;
        }
    }
    return false;
}

/* Heuristic function (Manhattan distance)*/
int heuristic(Point a, Point b)
{
    return abs(a.col - b.col) + abs(a.row - b.row);
}

/* A* Search Algorithm implementation*/
Point* aStar(char ** map, Point start, Point goal)
{
    /* List of nodes to be evaluated*/
    List openList = { 0 };
    /* List of nodes already evaluated*/
    List closedList = { 0 };

    /* Add the start node to the open list*/
    addToList(
        &openList,
        createNode(start, NULL, 0, heuristic(start, goal)));

    /* Main loop*/
    while (openList.size > 0) {
        /* Get the node with the lowest 'f' value*/
        Node* current = getLowestF(&openList);

        /* Check if the goal is reached*/
        if (current->pos.col == goal.col
            && current->pos.row == goal.row) {
            /* Path found, reconstruct and return*/
            int pathLength = 0;
            Node* pathNode = current;
            while (pathNode) {
                pathLength++;
                pathNode = pathNode->parent;
            }

            Point* path = (Point*)malloc(pathLength
                                         * sizeof(Point));
            pathNode = current;
            int i = 0;
            for (i = pathLength - 1; i >= 0; i--) {
                path[i] = pathNode->pos;
                pathNode = pathNode->parent;
            }
            /* Return the found path*/
            return path;
        }

        /* Move the current node to the closed list*/
        addToList(&closedList, current);

        /* Generate successors (4 possible movements)*/
        Point left = { current->pos.col - 1, current->pos.row };
        Point right = { current->pos.col + 1, current->pos.row };
        Point up = { current->pos.col, current->pos.row - 1 };
        Point down = { current->pos.col, current->pos.row + 1 };
        Point* successors = (Point*)malloc(MAX_SUCCESSORS * sizeof(Point));
        successors[0] = left;
        successors[1] = right;
        successors[2] = up;
        successors[3] = down;
       
        /* Evaluate each successor*/
        int i = 0;
        for (i = 0; i < MAX_SUCCESSORS; i++) {
            Point successor = successors[i];

            /* Check if the successor is within the grid and not an obstacle*/
            if (map[successor.row][successor.col] == '-'
                || map[successor.row][successor.col] == '|'
                || map[successor.row][successor.col] == 'o'
                || map[successor.row][successor.col] == '#'
                || isInList(&closedList, successor)) {
                continue;
            }
            else{
                /* Increment the cost*/
                int newG = current->g + 1;
                /* Calculate the heuristic*/
                int newH = heuristic(successor, goal);
                /* Calculate the total cost*/
                int newF = newG + newH;

                /* Check if this path is better than any previously found path*/
                if (!isInList(&openList, successor)
                    || newF < current->f) {
                    addToList(
                        &openList,
                        createNode(successor, current, newG,
                                newH)); /* Add to open list*/
                }
            }
        }
        free(successors);
    }
    /* No path found*/
    return NULL;
}
