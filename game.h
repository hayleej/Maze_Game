/*
 * File Name: game.h
 * Author: Haylee Jackson
 * Purpose: header file for game.c
 * Last Modified: 09/10/2021
 *  
*/

#ifndef GAME_H
#define GAME_H

#include "terminal.h"
#include "map.h"
#include "linkedList.h"
#include "enemy.h"


#define FALSE 0
#define TRUE !FALSE


typedef void (*CommandPtr)(char **, MapObject *, MapObject *);

typedef struct SavedMove
{
    char ** sMap;
    MapObject sPlayer;
    MapObject sEnemy;
} SavedMove;



void printMap( char ** map, int mapRow, int mapCol );
CommandPtr controlFunc( char command );
void up( char ** map, MapObject * player, MapObject * enemy );
void down( char ** map, MapObject * player, MapObject * enemy );
void left( char ** map, MapObject * player, MapObject * enemy );
void right( char ** map, MapObject * player, MapObject * enemy );
void undo( LinkedList * undoList, char *** map, MapObject * player, MapObject * enemy, int mapRow );
void copy( char ** saveMap, char ** map, int mapRow, int mapCol );
void save( LinkedList * undoList, char ** map, int mapRow, int mapCol, MapObject player, MapObject enemy );
void freeSavedMap( LinkedList * undoList, int mapRow );

#endif
