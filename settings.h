/*
 * File Name: settings.h
 * Author: Haylee Jackson
 * Purpose: header file for settings.c
 * Last Modified: 10/08/2025
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <time.h>
#include "startScreen.h"

typedef struct Game {
    char name[25];
    struct tm * last_played;
    char map_file[36];
    int level; /* level = -1 when not playing levels */
} Game;

typedef struct SavedGames {
    /* Array of Game pointers */
    Game* games[9];
    /* Current size of the list */
    int size;
} SavedGames;


Game* createGame(char* name, char* mapFile, int level, struct tm * lastPlayed);
void addToSavedGamesList(SavedGames* savedGames, Game* game);
void displaySavedGames(SavedGames savedGames);
void freeSavedGames( SavedGames savedGames);
Game * removeGameFromSavedGames(SavedGames * savedGames, char * name);

#endif
