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
            for ( i = 0; i < *metadataAmount; i++ )
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
    int row = 0, col = 0, objectCode = 0;

    /* write first line of file containing metadataAmount, mapRow and mapCol */
    fprintf(outFile, "%d %d %d\n", metadataAmount, mapRow, mapCol);

    
    /* read row, column, and object from map, and output to saved file */
    for ( row = 0; row < mapRow; row++ )
    {
        for (col = 0; col < mapCol; col++)
        {
            objectCode = whichObjectCode(map[row][col]);

            if ((0 <= objectCode) && (objectCode <= 3))
            {
                /* objectCode is wall, player, goal, or enemy */
                fprintf(outFile, "%d %d %d\n", row, col, objectCode);
            }
            
        }
    }
    
    fclose( outFile );
}


/**
 * @brief  reads file containing saved games 
 * @param  filename: name of the file containing saved games
 * @retval saved games
 */
SavedGames readSavedGames(char * filename)
{

    /* format of file is:
    * first line contains number of how many saved games
    * [name of game] [map.out] [level] [day] [month] [year] [hour] [minute]
    * */
    SavedGames savedGames = { 0 };
    FILE* inFile = fopen(filename, "r");
    int nRead = 0;
    int i = 0;
    int day, month, year, hour, minute;
    char gameName[25];
    time_t now = time(NULL);
    struct tm * lastPlayed = localtime(&now);
    char map_file[100];
    int level; /* level = -1 when not playing levels */
    int size;

    if ( inFile == NULL )
    {
        perror( "Error opening the file" );
    }
    else
    {
        /* reading first line of file containing metadataAmount, mapRow and mapCol */
        nRead = fscanf( inFile, "%d", &size );

        if ( nRead != 1 || nRead == EOF )
        {
            perror( "Error reading from file" );
        }
        else
        {

            /* read name, map file, level, and date and time from file */
            for ( i = 0; i < size; i++ )
            {
                nRead = fscanf( inFile, "%s %s %d %d %d %d %d %d\n", gameName, map_file, &level, &day, &month, &year, &hour, &minute );

                if ( nRead != 8 || nRead == EOF)
                {
                    perror( "Error reading from file" );
                }
                else
                {
                    lastPlayed->tm_mday = day;
                    lastPlayed->tm_mon = month;
                    lastPlayed->tm_year = year;
                    lastPlayed->tm_hour = hour;
                    lastPlayed->tm_min = minute;

                    /* add game to saved games */
                    addToSavedGamesList(&savedGames, createGame(gameName, map_file, level, lastPlayed));
                    
                }
            }
        }
    
        if ( ferror( inFile ) )
        {
            perror( "Error reading from file" );
        }

        fclose( inFile );
    }
    return savedGames;
}


void writeSavedGames(char * filename, SavedGames savedGames)
{

    /* format of file is:
    * first line contains number of how many saved games
    * [name of game] [map.out] [level] [day] [month] [year] [hour] [minute]
    * */
    int i = 0;

    FILE* outFile = fopen(filename, "w");

    /* write first line of file containing the number of saved games */
    fprintf(outFile, "%d\n", savedGames.size);

    
    /* read row, column, and object from map, and output to saved file */
    for ( i = 0; i < savedGames.size; i++ )
    {
        fprintf(outFile, "%s %s %d %d %d %d %d %d\n", savedGames.games[i]->name, 
            savedGames.games[i]->map_file, savedGames.games[i]->level, 
            savedGames.games[i]->last_played->tm_mday, 
            savedGames.games[i]->last_played->tm_mon, 
            savedGames.games[i]->last_played->tm_year, 
            savedGames.games[i]->last_played->tm_hour, 
            savedGames.games[i]->last_played->tm_min);     
    }
    
    fclose( outFile );
}
