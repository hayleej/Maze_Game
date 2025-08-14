/*
 * File Name: main.c
 * Author: Haylee Jackson
 * Purpose: the main function for the maze game
 * Last Modified: 09/10/2021
 * 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "map.h"
#include "fileIO.h"
#include "linkedList.h"
#include "startScreen.h"
#include "settings.h"




/* should have function for saving game */
void saveGame(SavedGames savedGames, char* name, char* map_file, int level)
{
    /* get current time as last played */
    time_t now = time(NULL);
    struct tm * lastPlayed = localtime(&now);
    /* add game to saved games list */
    addToSavedGamesList(&savedGames, createGame(name, map_file, level, lastPlayed));
    
    /* output to saved games file */
    writeSavedGames("saved/savedGames.out", savedGames);

}

void updateSavedGame(SavedGames savedGames, Game * game, int level)
{
    /* get current time as last played */
    time_t now = time(NULL);
    struct tm * lastPlayed = localtime(&now);
    /* update game in saved games list */
    game->level = level;
    game->last_played = lastPlayed;

    /* output to saved games file */
    writeSavedGames("saved/savedGames.out", savedGames);
}


char * getGameName()
{
    char option;
    char * saved_map_name = (char *) malloc(sizeof(char) * 25);
    char * sPtr;
    do
    {
        printf("Enter name of game to save:\n");
        /* select path to output saved game map */
        sPtr = fgets(saved_map_name, sizeof(saved_map_name), stdin);
        if ( sPtr == NULL )
        {
            if (ferror(stdin))
            {
                perror("Error reading name of saved game");
            }
            
        }
        else
        {
            saved_map_name[strcspn(saved_map_name, "\n")] = 0; /* Remove the newline character if present */
            
            printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]", saved_map_name);

            disableBuffer();
            scanf( "%c", &option );
            enableBuffer();
        }
    } while ((option != 'y') && (option != '0')); /* until confirmed name or 0 used to exit */
    
    if (option == '0')
    {
        return NULL; /* making sure it is still NULL */
    }
    
    return saved_map_name;
}
void exitGame(char ** map, int mapRow, int mapCol, int metadataAmount, SavedGames savedGames, int level, Game * game)
{
    char option;
    char * saved_map_name = NULL; /* 25 characters - specified in getGameName*/
    char saved_map_path[36] ="saved/";
    char * sPtr;
    /* exiting game */
    printf( "Exiting game...\n" );
    
    do
    { 
        /* save progress prompt */
        printf( "Do you want to save your progress? [y/n]\n" );
        disableBuffer();
        scanf( "%c", &option );
        if ((option != 'y') && (option != 'n' ))
        {
            /* print error */
            printf("ERROR: %c is an invalid option. Please select y or n",option);
        }
    
    } while ( !((option == 'y') || (option == 'n' ) )); /* correct option has not been selected */
    enableBuffer();
    if (option == 'y')
    {
        if (game == NULL)
        {
            /* ask for name of saved game */
            saved_map_name = getGameName();
        }
        else
        {
            do
            {
                printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]", game->name);

                disableBuffer();
                scanf( "%c", &option );
                enableBuffer();
            } while ((option != 'y') && (option != 'n') && (option != '0')); /* until confirmed name or 0 used to exit */

            if (option == 'y')
            {
                saved_map_name = (char *) malloc(sizeof(char) * 25);
                strcpy(saved_map_name, game->name);
            }
            else if (option == 'n')
            {
                level = game->level;
                saved_map_name = getGameName();
                free(removeGameFromSavedGames(&savedGames, game->name)); /* remove it so you can add it properly with new name */
                game = NULL;        
            }
        }
        
        if ((saved_map_name != NULL) && (option != '0'))
        {
            strcat(saved_map_path, saved_map_name);
            strcat(saved_map_path, ".out");
            /* save progress */
            writeSaveFile( saved_map_path, map, mapRow, mapCol, metadataAmount);
            if (game == NULL)
            {
                /* adding game to savedGames */
                saveGame(savedGames, saved_map_name, saved_map_path, level);
            }
            else
            {
                /* updating game */
                updateSavedGame(savedGames, game, level);
            }
            
            
            free(saved_map_name);
        }
        
        
    }
    
}

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
    char * gameName = NULL;
    Game * game = NULL;

    if ( argc == 2 )
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
        } while ( !((option == '1') || (option == '2' ) || (option == '3' ) || (option == '0' )) ); /* correct option has not been selected */

        enableBuffer();

        if (option == '3')
        {
            /* enter custom map path */
            system( "clear" );
            printTitle(MIN_LENGTH);
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
            
            
        }
        else if (option == '2')
        {
            
            char upperOption = savedGames.size + '0';
            do
            {
                /* display saved games */
                displaySavedGames(savedGames);
                printLine("Which game do you want to load?", MIN_LENGTH);
                disableBuffer();
                /* select saved game option*/
                scanf( "%c", &option );
            } while ((option != '0') && (option < '1') && (option > upperOption)); /* until a saved game is chosen or exit game */
            
            enableBuffer();
            if (option != '0')
            {
                /* get saved game */
                game = savedGames.games[(option + 0) - 49];
                /* load saved map */
                map = readFile( game->map_file, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
            }
            
        }
        else
        {   
            char mapfile[16] = "maps/levelx.txt";
            mapfile[10] = level + '0';
            map = readFile( mapfile, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
        }
        

        if ((map != NULL) && (option != '0')) /* user hasn't exited game */
        {
            /* map has been initialized */
            command = playGame(&map, mapRow, mapCol, &player, &enemy, &goal);
            
            if ((game != NULL) && (command != '0'))
            {
                /* if won or lost saved game remove from saved games */
                removeGameFromSavedGames(&savedGames, game->name);
                /* update saved games file */
                writeSavedGames("saved/savedGames.out", savedGames);
            }
            
            if (command == '0')
            {
                exitGame(map, mapRow, mapCol, metadataAmount, savedGames, level, game);
                
            }
            else if ( ( player.row == goal.row ) && ( player.col == goal.col ) )
            {
                /* game is won */
                printMap( map, mapRow, mapCol );
                printf( "You Win!\n" );
            }
            else
            {
                /* game is lost */
                printMap( map, mapRow, mapCol );
                printf( "You Lost!\n" );
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

