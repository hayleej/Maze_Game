/*
 * File Name: main.c
 * Author: Haylee Jackson
 * Purpose: the main function for the maze game
 * 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


int main( int argc, char *argv[] )
{ 
    /* variable declarations */
    MapObject player = {'^', 0, 0};
    MapObject enemy = {'~', 0, 0};
    MapObject goal = {'x', 0, 0};
    char ** map = NULL;
    int  mapRow = 0, mapCol = 0, metadataAmount = 0;
    char command;
    char option;
    char map_path [100];
    char errorLevelMessage[55];
    SavedGames savedGames;
    char * sPtr;
    int level = 1;
    Game * game = NULL;
    char mapfile[16] = "maps/levelx.txt";

    if ( argc == 1 )
    {   
        /* read saved games file */
        savedGames = readSavedGames("saved/savedGames.out");
        do
        { 
            /* display start screen */
            printStartScreen(errorLevelMessage, MIN_LENGTH);
            
            disableBuffer();
            /* select map option*/
            scanf( "%c", &option );
            strcpy(errorLevelMessage, "ERROR: x is an invalid option. Please select 1, 2 or 3");
            errorLevelMessage[7] = option;
        } while ( !((option == '1') || (option == '2' ) || (option == '3' ) || (option == EXIT_GAME )) ); /* correct option has not been selected */

        enableBuffer();

        /* load game map */
        if (option == '3')
        {
            /* enter custom map path */
            system( "clear" );
            printTitle(MIN_LENGTH);
            printExitCommandInfo(MIN_LENGTH);
            do
            {
                printf("Enter path to custom map:\n");
                /* select path to custom map */
                sPtr = fgets(map_path, sizeof(map_path), stdin);
                if ( sPtr == NULL )
                {
                    if (ferror(stdin))
                    {
                        perror("Error reading path of custom map");
                    }
                    
                }
                map_path[strcspn(map_path, "\n")] = 0; /* Remove the newline character if present */
                if (strcmp(map_path,"0") != 0)
                {
                    /* so to not print error opening file when trying to exit */
                    map = readFile( map_path, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
                }
                
            } while ((map == NULL) && (strcmp(map_path,"0") != 0)); /* until map_path is correct or 0 is used to exit */
            
            level = -1; /* for custom map */
        }
        else if (option == '2')
        {
            /* load saved games */

            char upperOption = savedGames.size + '0';
            do
            {
                /* display saved games */
                displaySavedGames(savedGames);
                printLine("Which game do you want to load?", MIN_LENGTH);
                disableBuffer();
                /* select saved game option*/
                scanf( "%c", &option );
            } while ((option != EXIT_GAME) && (option < '1') && (option > upperOption)); /* until a saved game is chosen or exit game */
            
            enableBuffer();
            if (option != EXIT_GAME)
            {
                /* get saved game */
                game = savedGames.games[(option + 0) - 49];
                /* load saved map */
                map = readFile( game->map_file, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
                level = game->level; /* update level */
            }
        }
        else
        {   
            /* start new game */
            mapfile[10] = level + '0';
            map = readFile( mapfile, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
        }
        
        /* play game */
        if ((map != NULL) && (option != EXIT_GAME)) /* user hasn't exited game */
        {
            /* map has been initialized */
            command = playGame(&map, mapRow, mapCol, &player, &enemy, &goal);

            if (command == EXIT_GAME)
            {
                /* exit game and save */
                exitGame(map, mapRow, mapCol, metadataAmount, savedGames, level, game);
            }
            else if ((command == WON_GAME) && (level != -1) && (level < MAX_LEVEL))
            {
                do
                { 
                    /* Won game, playing levels, not on last level */
                    level ++;

                    /* read map of next level */
                    freeMap( map, mapRow );
                    mapfile[10] = level + '0';
                    map = readFile( mapfile, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
                    /* play game */
                    command = playGame(&map, mapRow, mapCol, &player, &enemy, &goal);
                } while ((command == WON_GAME) && (level < MAX_LEVEL)); /* won game and still more levels */
                
                if (command == EXIT_GAME)
                {
                    /* exit and save game */
                    exitGame(map, mapRow, mapCol, metadataAmount, savedGames, level, game);
                }
                else if (command == LOST_GAME)
                {
                    /* lost game */
                    printMap( map, mapRow, mapCol );
                    printf( "You Lost!\n" );
                }
                else
                {
                    /* won final level */
                    printMap( map, mapRow, mapCol );
                    printf( "You Win!\n" );
                }
            }
            else if (command == LOST_GAME)
            {
                /* lost game (custom or level game) */
                printMap( map, mapRow, mapCol );
                printf( "You Lost!\n" );
            }
            else if (level == -1)
            {
                /* won custom game */
                printMap( map, mapRow, mapCol );
                printf( "You Win!\n" );
            }
            
            if ((game != NULL) && (command != EXIT_GAME))
            {
                /* if won or lost saved game remove from saved games */
                game = removeGameFromSavedGames(&savedGames, game->name);
                
                /* remove map file from saved/ folder */
                if(remove(game->map_file) != 0)
                {
                    /* error deleting file */
                    printf("Error: Unable to delete the file: %s.\n", game->map_file);
                }
                free(game);
                /* update saved games file */
                writeSavedGames("saved/savedGames.out", savedGames);
            }
        }
        
        /* free malloced memory */
        freeMap( map, mapRow );
        freeSavedGames(savedGames);
    }
    else
    { 
        /* Error when number of command line arguments is not equal to 2 */
        printf( "Error: Not the right number of arguements in the command line." );
    }
    return 0;
}

