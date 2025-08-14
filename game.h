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
#include "startScreen.h"
#include "settings.h"
#include "fileIO.h"

#define FALSE 0
#define TRUE !FALSE

#define MAX_LEVEL 3
#define EXIT_GAME '0'
#define LOST_GAME 'L'
#define WON_GAME 'W'


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
char playGame(char *** map, int mapRow, int mapCol, MapObject * player, MapObject * enemy, MapObject * goal);
void exitGame(char ** map, int mapRow, int mapCol, int metadataAmount, SavedGames savedGames, int level, Game * game);
char * getGameName();
void updateSavedGame(SavedGames savedGames, Game * game, int level);
void saveGame(SavedGames savedGames, char* name, char* map_file, int level);

#endif
