/*
 * File Name: map.h
 * Author: Haylee Jackson
 * Purpose: header file for map.c
 * Last Modified: 09/10/2021
*/

#ifndef MAP_H
#define MAP_H

#define PLAYER 0
#define ENEMY 1
#define GOAL 2
#define WALL 3

typedef struct MapObject {
    char obj;
    int row;
    int col;
} MapObject;
 
void insertObject( char *** mapPtr, int row, int col, MapObject * object );
void whichObject( int objectCode, char *** mapPtr, int row, int col, MapObject * player, MapObject * enemy, MapObject * goal );
char** initializeMap( int mapRow, int mapCol );
int whichObjectCode(char object);
void freeMap( char ** map, int mapRow );


#endif
