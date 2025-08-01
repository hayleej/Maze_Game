/*
 * File Name: map.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the map of the maze
 * Last Modified: 09/10/2021
*/

#include <stdlib.h>
#include "map.h"


/**
 * @brief  insert object into map
 * @param  mapPtr: pointer to map
 * @param  row: the map row the object is in
 * @param  col: the map column the object is in
 * @param  object: object being inserted into map
 * @retval None
 */
void insertObject( char *** mapPtr, int row, int col, MapObject * object )
{   
    (*mapPtr)[row][col] = object->obj;
    object->row = row;
    object->col = col;
}








/**
 * @brief  inserts player, goal, enemy, or wall into map based on objectCode
 * @param  objectCode: the object's code
 * @param  mapPtr: pointer to map
 * @param  row: the map row the object is in
 * @param  col: the map column the object is in 
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @param  goal: symbol and location of goal in map
 * @retval None
 */
void whichObject( int objectCode, char *** mapPtr, int row, int col, MapObject * player, MapObject * enemy, MapObject * goal )
{
    if ( objectCode == PLAYER )
    {
        insertObject( mapPtr, row, col, player );
    }
    else if ( objectCode == ENEMY )
    {
        insertObject( mapPtr, row, col, enemy );
    }
    else if ( objectCode == GOAL )
    {
        insertObject( mapPtr, row, col, goal );
    }
    else if ( objectCode == WALL )
    {
        (*mapPtr)[row][col] = 'o';
    }
}








/**
 * @brief  creates the map with border and spaces
 * @note   From UCP Assignment 1 where it was a part of createMap() function, but has now been edited into its own function
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @retval empty map with border
 */
char** initializeMap( int mapRow, int mapCol )
{
    /* variable declarations */ 
    int i, j;
    char ** map;

    /* allocate heap memory for map */
    map = (char **) malloc( sizeof(char *) * mapRow ) ;
    for ( i = 0; i < mapRow ; i++)
    { 
        map[i] = (char *) malloc( sizeof(char) * mapCol );
    }

    /* initialize map with space characters in the 2D array*/
    for ( i = 1; i < mapRow - 1; i++ )
    { 
        for ( j = 1; j < mapCol - 1; j++ )
        { 
            map[i][j] = ' ';
        }
        
    }

    /*create border of map */
    for ( i = 1; i < mapRow - 1; i++ )
    { 
        map[i][0] = '|';
        map[i][mapCol - 1] = '|';
    }

    for ( j = 1; j < mapCol - 1; j++ )
    { 
        map[0][j] = '-';
        map[mapRow - 1][j] = '-';
    }

    /*create corners of map */
    map[0][0] = '#';
    map[mapRow - 1][0] = '#';
    map[0][mapCol - 1] = '#';
    map[mapRow - 1][mapCol - 1] = '#';

    return map;
}








/**
 * @brief  frees heap memory of map
 * @note   From UCP Assignment 1 where it was a part of main() function, but has now been edited into its own function
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @retval None
 */
void freeMap( char ** map, int mapRow )
{
    int i;

    for ( i = 0; i < mapRow; i++ )
    { 
        free( map[i] );
    }

    free( map );
}
