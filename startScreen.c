/*
 * File Name: game.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the start screen and settings of game
 * Last Modified: 07/08/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "startScreen.h"

void printTitle( int length )
{

    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    /* print top border */
    printBorder(length);
    
    printLine("Maze Game!", length);
    
    /* print bottom border */
    printBorder(length);
    /*printLine(" ", length);*/
}

void printStartScreen( char * errorLevelMessage, int length )
{

    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    system( "clear" );

    /* print top border */
    printBorder(length);
    
    printLine("Welcome to", length);
    printLine("Maze Game", length);
    
    /* print bottom border */
    printBorder(length);

    printLine("Select 0 at any time to exit the game", length);

    printBorder(length);
    
    printLine("Select your difficulty level:", length);
    printLine("(1) easy", length);
    printLine("(2) hard", length);
    

    printBorder(length);
    printf("%s\n", errorLevelMessage);
}

void printLine( char * line, int length)
{
    if (length < MIN_LENGTH)
    {
        /* length should be min length or greater 
         * this is mainly for when length is the number of columns in the map
        */

        length = MIN_LENGTH;
    }
    
    char finalLine[length];
    int lineLength = strlen(line);
    int blank_each_side = (length - lineLength) / 2;
    
    int i; 
    finalLine[0] = '*';
    for ( i = 1; i < blank_each_side; i++ )
    { 
        finalLine[i] =  ' ';
    }

    for ( i = blank_each_side; i < blank_each_side + lineLength; i++ )
    { 
        finalLine[i] =  line[i - blank_each_side];
    }
    for ( i = blank_each_side + lineLength; i < length - 1; i++ )
    { 
        finalLine[i] =  ' ';
    }
    finalLine[length - 1] = '*';
    
    printf("%s\n",finalLine);
}

void printBorder( int length)
{
    int i;

    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    printf("* "); /* corner of border */
    for ( i = 0; i < length - 4; i+=2 )
    { 
        printf( "* " );
    }
    printf("*\n");
}
