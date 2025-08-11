/*
 * File Name: settings.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the settings of the game
 * Last Modified: 10/08/2025
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "settings.h"


Game* createGame(char* name, char* mapFile, int level, struct tm * lastPlayed)
{
    Game* game = (Game*)malloc(sizeof(Game));
    strcpy(game->name, name);
    strcpy(game->map_file, mapFile);
    game->level = level;
    game->last_played = lastPlayed;
    return game;
}

/* Function to add a game to a list*/
void addToSavedGamesList(SavedGames* savedGames, Game* game)
{
    savedGames->games[savedGames->size++] = game;
}
void displaySavedGames(SavedGames savedGames)
{
    int i;
    /*struct tm * lastPlayed;*/
    char formattedTime[11];
    char line[41] = "(x) ";

    
    /* display saved games name and last played */

    printTitle( MIN_LENGTH );

    printLine( "Saved Games:", MIN_LENGTH );

    printDivider(MIN_LENGTH);
    printLine("Name      Last Played", MIN_LENGTH);
    printDivider(MIN_LENGTH);

    /* print saved games name and last played */
    for ( i = 0; i < savedGames.size; i++)
    {
        strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y", savedGames.games[i]->last_played);
        line[1] = (i + 1) + '0';
        strcat(line,savedGames.games[i]->name);
        strcat(line, "  ");
        /* combine name and formatted time */
        strcat(line, formattedTime);
        printLine(line, MIN_LENGTH);
        strcpy(line, "(x) ");
    }
    
    
    /* file layout is the number of saved games\n then each line is the name, last played, mapfile, and level*/

}


/* should have function for saving game */
void saveGame(SavedGames savedGames, char* name, char* map_file, int level)
{
    /*Game game = {name, time(NULL), map_file, level};*/

    /* output to saved games file */

}

/**
 * @brief  frees heap memory of savedGames
 * @param  savedGames: savedGames
 * @param  savedNum: number of savedGames
 * @retval None
 */
void freeSavedGames( SavedGames savedGames)
{
    int i;

    for ( i = 0; i < savedGames.size; i++ )
    { 
        free( savedGames.games[i] );
    }
}
