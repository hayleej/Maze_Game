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

#define MIN_LENGTH 41

void printBorder( int length);
void printStartScreen( char * errorLevelMessage, int length );
void printLine( char * line, int length);
void printTitle( int length ); 

#endif
