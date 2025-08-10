/*
 * File Name: fileIO.c
 * Author: Haylee Jackson
 * Purpose: All functions related to file io for the game
 * Last Modified: 09/10/2021
*/

#include <stdio.h>
#include <string.h>
#include "fileIO.h"


/**
 * @brief  reads file containing map data and creates map
 * @param  filename: the name of the file to read in
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @param  goal: symbol and location of goal in map
 * @param  metadataAmount: the amount of objects in the map
 * @retval map of maze game
 */
char** readFile( char* filename, int * mapRow, int * mapCol, MapObject * player, MapObject * enemy, MapObject * goal, int * metadataAmount )
{

    FILE* inFile = fopen(filename, "r");
    int nRead = 0;
    char ** map = NULL;
    int i = 0;
    int row = 0, col = 0, objectCode = 0;

    if ( inFile == NULL )
    {
        perror( "Error opening the file" );
    }
    else
    {
        /* reading first line of file containing metadataAmount, mapRow and mapCol */
        nRead = fscanf( inFile, "%d %d %d", metadataAmount, mapRow, mapCol );

        if ( nRead != 3 || nRead == EOF )
        {
            perror( "Error reading from file" );
        }
        else
        {
            map = initializeMap( *mapRow, *mapCol );

            /* read row, column, and object code from file */
            for ( i = 0; i < metadataAmount; i++ )
            {
                nRead = fscanf( inFile, "%d %d %d", &row, &col, &objectCode );

                if ( nRead != 3 || nRead == EOF)
                {
                    perror( "Error reading from file" );
                }
                else
                {
                    whichObject( objectCode, &map, row, col, player, enemy, goal );
                }
            }
        }
    
        if ( ferror( inFile ) )
        {
            perror( "Error reading from file" );
        }

        fclose( inFile );
    }
    return map;
}


/**
 * @brief  Output saved map data when exiting game in progress
 * @param  filename: the name of the file to write to
 * @param  map: map of maze game
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @param  metadataAmount: the amount of objects in the map
 * @retval None
 */
void writeSaveFile( char* filename, char ** map, int mapRow, int mapCol, int metadataAmount)
{

    FILE* outFile = fopen(filename, "w");
    int nRead = 0;
    int row = 0, col = 0, objectCode = 0;

    /* write first line of file containing metadataAmount, mapRow and mapCol */
    fprintf(outFile, "%d %d %d", metadataAmount, mapRow, mapCol);

    
    /* read row, column, and object from map, and output to saved file */
    for ( row = 0; row < mapRow; row++ )
    {
        for (col = 0; col < mapCol; col++)
        {
            objectCode = whichObjectCode(map[row][col]);

            if ((0 <= objectCode) || (objectCode <= 3))
            {
                /* objectCode is wall, player, goal, or enemy */
                fprintf(outFile, "%d %d %d", row, col, objectCode);
            }
            
        }
    }
    
    fclose( outFile );
}
