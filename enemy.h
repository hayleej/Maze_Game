/*
 * File Name: enemy.h
 * Author: Haylee Jackson
 * Purpose: header file for enemy.c
 * Last Modified: 09/10/2021
*/

#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"
#include "game.h"
#include "searchAlgorithm.h"

void moveEnemy( char ** map, MapObject * enemy, MapObject * player );
void enemyUpDown( char ** map, MapObject * enemy, MapObject * player );
void enemyLeftRight( char ** map, MapObject * enemy, MapObject * player );

#endif
