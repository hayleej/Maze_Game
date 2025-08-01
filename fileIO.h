/*
 * File Name: fileIO.h
 * Author: Haylee Jackson
 * Purpose: header file for fileIO.c
 * Last Modified: 09/10/2021
*/

#ifndef FILEIO_H
#define FILEIO_H 

#include "map.h"

char** readFile( char* filename, int * mapRow, int * mapCol, MapObject * player, MapObject * enemy, MapObject * goal );

#endif
