/*
 * File Name: game.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the game features
 * Last Modified: 09/10/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


/**
 * @brief  prints the map to the terminal
 * @note   From UCP Assignment 1, but has been edited
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @retval None
 */
void printMap( char ** map, int mapRow, int mapCol )
{ 
    /* variable declarations */
    int i, j; 

    system( "clear" );

    /* print map with for loop */
    for ( i = 0; i < mapRow; i++ )
    { 
        for ( j = 0; j < mapCol; j++ )
        { 
            printf( "%c", map[i][j] );
        }
        printf( "\n" );   
    }
}





/**
 * @brief  processes the user's input to move the player
 * @param  command: user's input
 * @retval a pointer to a function that moves the player in the direction specified by the command
 */
CommandPtr controlFunc( char command )
{
    CommandPtr option = NULL;

    if ( command == 'w' )
    {
        option = &up;
    }
    else if ( command == 's' )
    {
        option = &down;
    }
    else if ( command == 'a' )
    {
        option = &left;
    }
    else if ( command == 'd' )
    {
        option = &right;
    }

    return option;
}






/**
 * @brief  moves the player up 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void up( char ** map, MapObject * player, MapObject * enemy )
{
    /* move up */
    if ( ( map[player->row - 1][player->col] == ' ' ) || ( map[player->row - 1][player->col] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->row = player->row - 1;
        map[player->row][player->col] = '^';
        player->obj = '^';
    }
    moveEnemy(map, enemy, player);
}






/**
 * @brief  moves the player down 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void down( char ** map, MapObject * player, MapObject * enemy )
{
    /* move down */
    if ( ( map[player->row + 1][player->col] == ' ' ) || ( map[player->row + 1][player->col] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->row = player->row + 1;
        map[player->row][player->col] = 'v';
        player->obj = 'v';
    }
    moveEnemy(map, enemy, player);
}






/**
 * @brief  moves the player left 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void left( char ** map, MapObject * player, MapObject * enemy )
{
    /* move left */
    if ( ( map[player->row][player->col - 1] == ' ' ) || ( map[player->row][player->col - 1] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->col = player->col - 1;
        map[player->row][player->col] = '<';
        player->obj = '<';
    }
    moveEnemy(map, enemy, player);
}







/**
 * @brief  moves the player right 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void right( char ** map, MapObject * player, MapObject * enemy )
{
    /* move right */
    if ( ( map[player->row][player->col + 1] == ' ' ) || ( map[player->row][player->col + 1] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->col = player->col + 1;
        map[player->row][player->col] = '>';
        player->obj = '>';
    }
    moveEnemy(map, enemy, player);
}







/**
 * @brief  undo feature to undo previous move
 * @param  undoList: linked list containing past moves in game
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @param  mapRow: the number of rows in map
 * @retval None
 */
void undo( LinkedList * undoList, char *** map, MapObject * player, MapObject * enemy, int mapRow )
{
    SavedMove * prevMove = NULL;

    if ( undoList->count != 0 )
    {
        prevMove = (SavedMove *)removeStart( undoList );
        freeMap( *map, mapRow ); /* free memory of current map */
        *map = prevMove->sMap;
        *player = prevMove->sPlayer;
        *enemy = prevMove->sEnemy;
        free( prevMove );
    }
}





/**
 * @brief  copies map to saveMap
 * @param  saveMap: where the map is being copied to
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @retval None
 */
void copy( char ** saveMap, char ** map, int mapRow, int mapCol )
{
    int i;
    for ( i = 0; i < mapRow ; i++ )
    { 
        memcpy( saveMap[i], map[i], sizeof(char) * mapCol );
    }
}






/**
 * @brief  saves the current move to the undoList 
 * @param  undoList: linked list containing past moves in game
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void save( LinkedList * undoList, char ** map, int mapRow, int mapCol, MapObject player, MapObject enemy )
{
    SavedMove * move;
    char ** saveMap = initializeMap( mapRow, mapCol );
    copy( saveMap, map, mapRow, mapCol ); 
    move  = (SavedMove *) malloc( sizeof(SavedMove) ); 

    move->sMap = saveMap; 
    move->sPlayer = player; 
    move->sEnemy = enemy; 
    insertStart( undoList, move );
}




/**
 * @brief  frees the maps in the past moves in the undoList
 * @param  undoList: linked list containing past moves in game
 * @param  mapRow: number of rows in map
 * @retval None
 */
void freeSavedMap( LinkedList * undoList, int mapRow )
{
    LinkedListNode * pCur = undoList->head;
    LinkedListNode * pTemp = NULL;
    SavedMove * saved = NULL;

    while ( pCur )
    {
        pTemp = pCur->next;

        /* free pCur's savedMove map */
        saved = (SavedMove *)pCur->data;
        freeMap( saved->sMap, mapRow );

        pCur = pTemp;
    }
}
