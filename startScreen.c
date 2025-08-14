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

/**
 * @brief  prints the title Maze Game with border
 * @param  length: the number of characters per line
 * @retval None
 */
void printTitle( int length )
{
    system( "clear" );
    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    /* print top border */
    printBorder(length);

    printf("\033[1m");
    printLine("Maze Game!", length);
    printf("\033[0m");
    printBorder(length);
}

/**
 * @brief  prints the "Select 0 at any time to exit" line with border
 * @param  length: the number of characters per line
 * @retval None
 */
void printExitCommandInfo( int length )
{
    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }
    /* print bottom border */
    /*printBorder(length);*/

    printf("\033[3m");
    printLine("Select 0 at any time to exit the game", length);
    printf("\033[0m");

    /* print bottom border */
    printBorder(length);
}

/**
 * @brief  prints the start screen for maze game 
 * @param  errorLevelMessage: error message for if user has inputted invalid option, otherwise blank
 * @param  length: the number of characters per line
 * @retval None
 */
void printStartScreen( char * errorLevelMessage, int length )
{

    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    system( "clear" );

    /* print top border */
    printBorder(length);
    printf("\033[1m");
    printLine("Welcome to", length);
    printLine("Maze Game!", length);
    printf("\033[0m");

    /* print bottom border */
    printBorder(length);


    printf("\033[3m");
    printLine("Select 0 at any time to exit the game", length);
    printf("\033[0m");
    printBorder(length);
    
    /* map option */
    printLine("Select game option:", length);
    printLine("(1) start new game ", length);
    printLine("(2) load saved game", length);
    printLine("(3) open custom map", length);
    

    printBorder(length);
    printf("%s\n", errorLevelMessage);
}

/**
 * @brief  prints a line with border for game
 * @param  line: the line to print
 * @param  length: the number of characters per line
 * @retval None
 */
void printLine( char * line, int length)
{
    if (length < MIN_LENGTH)
    {
        /* length should be min length or greater 
         * this is mainly for when length is the number of columns in the map
        */

        length = MIN_LENGTH;
    }
    
    char* finalLine = (char *) malloc( sizeof(char) * length ) ;
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
    free(finalLine);
}

/**
 * @brief  prints the top or bottom border of game
 * @param  length: the number of characters per line
 * @retval None
 */
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

void printDivider(int length)
{
    int i;

    if (length < MIN_LENGTH)
    {
        length = MIN_LENGTH;
    }

    /* print line of ---- */
    printf( "*" );
    for ( i = 1; i < length-1; i+=1 )
    { 
        printf( "-" );
    }
    printf( "*\n" );
}
