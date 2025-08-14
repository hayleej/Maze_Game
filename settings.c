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

/**
 * @brief  creates Game to save  
 * @param  name: name of the saved game
 * @param  mapFile: path to the saved map file
 * @param  level: the level the player is up to
 * @param  lastPlayed: struct tm of the date and time the game was last played
 * @retval the saved game
 */
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
    if (savedGames->size < 9)
    {
        savedGames->games[savedGames->size++] = game;
    }
    else
    {
        perror("Could not add game to saved games list");
    }
    
}

/* Function to check if a point is in a list*/
int isInSavedGames(SavedGames* savedGames, char* name)
{
    int index = -1;
    int i = 0;
    for (i = 0; i < savedGames->size; i++) {
        if (strcmp(savedGames->games[i]->name, name) == 0) {
            index = i;
        }
    }
    return index;
}

Game * removeGameFromSavedGames(SavedGames * savedGames, char * name)
{
    Game * game = NULL;
    int index = isInSavedGames(savedGames, name);
    if (index != - 1)
    {
        /* is in savedGames */
        game = savedGames->games[index];
        savedGames->games[index] = savedGames->games[--savedGames->size];
    }
    return game;
}

/**
 * @brief  displays the name and last played of the list of saved games
 * @param  savedGames: list of saved games
 * @retval None
 */
void displaySavedGames(SavedGames savedGames)
{
    int i;
    /*struct tm * lastPlayed;*/
    char formattedTime[11];
    char line[41] = "(x) ";

    
    /* display saved games name and last played */

    printTitle( MIN_LENGTH );
    printExitCommandInfo(MIN_LENGTH);
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
    
    printBorder(MIN_LENGTH);

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
