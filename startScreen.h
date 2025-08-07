/*
 * File Name: startScreen.h
 * Author: Haylee Jackson
 * Purpose: header file for startScreen.c
 * Last Modified: 07/08/2025
 *  
*/

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "terminal.h"

void printBorder( int length);
void printStartScreen( char * errorLevelMessage );
void printLine( char * line, int length);

#endif