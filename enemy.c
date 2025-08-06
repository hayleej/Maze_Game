/*
 * File Name: enemy.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the enemy feature
 * Last Modified: 09/10/2021
*/

#include <stdio.h>
#include "enemy.h"


/**
 * @brief  moves the enemy up or down towards the player 
 * @param  map: map of maze
 * @param  enemy: symbol and location of enemy in map
 * @param  player: symbol and location of player in map
 * @retval None
 */
void enemyUpDown( char ** map, MapObject * enemy, MapObject * player )
{
    int distance;

    distance = player->row - enemy->row;

    if ( distance > 0 )
    {
        /* 
         * player is below enemy
         * enemy moves down
         */
        if ( ( map[enemy->row + 1][enemy->col] == ' ' ) || ( map[enemy->row + 1][enemy->col] == player->obj ) )
        { 
            map[enemy->row][enemy->col] = ' ';
            enemy->row = enemy->row + 1;
            map[enemy->row][enemy->col] = '~';
        }
        else if ( map[enemy->row + 1][enemy->col] == 'o' )
        {
            /* object blocking enemy move */
            if (enemy->col == player->col)
            {
                /* enemy is in same col as player */
                
            }
            else
            {
                /* enemy cannot move down towards player so move left/right towards player */
                enemyLeftRight( map, enemy, player );
            }
            
        }

    }
    else if (distance < 0)
    {
        /* 
         * player is above enemy
         * enemy moves up
         */
        if ( ( map[enemy->row - 1][enemy->col] == ' ' ) || ( map[enemy->row - 1][enemy->col] == player->obj ) )
        { 
            map[enemy->row][enemy->col] = ' ';
            enemy->row = enemy->row - 1;
            map[enemy->row][enemy->col] = '~';
        }
        else if ( map[enemy->row - 1][enemy->col] == 'o' )
        {
            /* object blocking enemy move */
            if (enemy->col == player->col)
            {
                /* enemy is in same col as player */
                
            }
            else
            {
                /* enemy cannot move up towards player so move left/right towards player */
                enemyLeftRight( map, enemy, player );
            }
            
        }
    }
    else
    {
        /* enemy and player are in same row of map */
        enemyLeftRight( map, enemy, player );
    }
}







/**
 * @brief  moves the enemy left or right towards the player 
 * @param  map: map of maze
 * @param  enemy: symbol and location of enemy in map
 * @param  player: symbol and location of player in map
 * @retval None
 */
void enemyLeftRight( char ** map, MapObject * enemy, MapObject * player )
{
    int distance;

    distance = player->col - enemy->col;

    if ( distance > 0 )
    {
        /* 
         * player is to right of enemy
         * enemy moves right
         */
        if ( ( map[enemy->row][enemy->col + 1] == ' ' ) || ( map[enemy->row][enemy->col + 1] == player->obj ) )
        { 
            map[enemy->row][enemy->col] = ' ';
            enemy->col = enemy->col + 1;
            map[enemy->row][enemy->col] = '~';
        }
        else if ( map[enemy->row][enemy->col + 1] == 'o' )
        {
            /* object blocking enemy move */
            if (enemy->row == player->row)
            {
                /* enemy is in same row as player */

            }
            else
            {
                /* enemy cannot move right towards player so move down/up towards player */
                enemyUpDown( map, enemy, player );
            }
            
        }
        

    }
    else if (distance < 0)
    {
        /* 
         * player is to left of enemy
         * enemy moves left
         */
        if ( ( map[enemy->row][enemy->col - 1] == ' ' ) || ( map[enemy->row][enemy->col - 1] == player->obj ) )
        { 
            map[enemy->row][enemy->col] = ' ';
            enemy->col = enemy->col - 1;
            map[enemy->row][enemy->col] = '~';
        }
        else if ( map[enemy->row][enemy->col - 1] == 'o' )
        {
            /* object blocking enemy move */
            if (enemy->row == player->row)
            {
                /* enemy is in same row as player */
                
            }
            else
            {
                /* enemy cannot move left towards player so move down/up towards player */
                enemyUpDown( map, enemy, player );
            }
            
        }
    }
    else
    {
        /* enemy and player are in same column of map */
        enemyUpDown( map, enemy, player );
    }
}
