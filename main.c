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

int playGame(char *** map, int mapRow, int mapCol, MapObject * player, MapObject * enemy, MapObject * goal)
{
    LinkedList * undoList = NULL; 
    char command;
    CommandPtr pFunction;
    /* map has been initialized */

    undoList = createLinkedList(); 

    do
    { 
        printMap( *map, mapRow, mapCol );

        disableBuffer();
        scanf( " %c", &command );
        
        if ( command == 'u' )
        {
            undo( undoList, map, player, enemy, mapRow );
        }
        else if (command != '0')
        {
            pFunction = controlFunc( command );
            if ( pFunction != NULL )
            {
                save( undoList, *map, mapRow, mapCol, *player, *enemy ); 
                (*pFunction)( *map, player, enemy ); /* moves player */
            }
        }
    } while ( !( ( player->row == goal->row ) && ( player->col == goal->col ) ) && !( ( player->row == enemy->row ) && ( player->col == enemy->col ) ) && (command != '0')); /*game is not won and not lost */

    enableBuffer();
    
    /* free malloced memory */
    freeSavedMap( undoList, mapRow );
    freeLinkedList( undoList, &free );
    free( undoList );

    return command;
}


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

void exitGame(char ** map, int mapRow, int mapCol, int metadataAmount, SavedGames savedGames, int level, char * gameName)
{
    char option;
    char saved_map_name[25];
    char saved_map_path[36] ="saved/";
    char * sPtr;
    /* exiting game */
    printf( "Exiting game...\n" );
    
    do
    { 
        /* save progress prompt */
        printf( "Do you want to save your progress? [y/n]\n" );
        disableBuffer();
        scanf( " %c", &option );
        if ((option != 'y') && (option != 'n' ))
        {
            /* print error */
            printf("ERROR: %c is an invalid option. Please select y or n",option);
        }
    
    } while ( !((option == 'y') || (option == 'n' ) )); /* correct option has not been selected */
    enableBuffer();
    if (option == 'y')
    {
        if (gameName == NULL)
        {
            /* ask for name of saved game */
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
                    
                    strcat(saved_map_path, saved_map_name);
                    strcat(saved_map_path, ".out");

                    printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]", saved_map_name);

                    disableBuffer();
                    scanf( " %c", &option );
                    enableBuffer();
                }
            } while ((option != 'y') && (option != '0')); /* until confirmed name or 0 used to exit */
            
        }
        else
        {
            do
            {
                printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]", gameName);

                disableBuffer();
                scanf( " %c", &option );
                enableBuffer();
            } while ((option != 'y') && (option != '0')); /* until confirmed name or 0 used to exit */

            if (option == 'y')
            {
                strcpy(saved_map_name, gameName);
                strcat(saved_map_path, saved_map_name);
                strcat(saved_map_path, ".out");
            }
            
        }
        
        if (option == 'y')
        {
            /* save progress */
            writeSaveFile( saved_map_path, map, mapRow, mapCol, metadataAmount);
            saveGame(savedGames, saved_map_name, saved_map_path, level);
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
    

    if ( argc == 2 )
    {   
        do
        { 
            /* display start screen */
            printStartScreen(errorLevelMessage, MIN_LENGTH);
            /* read saved games file */
            savedGames = readSavedGames("saved/savedGames.out");
            displaySavedGames(savedGames);
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
            /* load saved map */
            map = readFile( "map.out", &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
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
            
            if ((gameName != NULL) && (command != '0'))
            {
                /* if won or lost saved game remove from saved games */
                removeGameFromSavedGames(&savedGames, gameName);
                /* update saved games file */
                writeSavedGames("saved/savedGames.out", savedGames);
            }
            
            if (command == '0')
            {
                exitGame(map, mapRow, mapCol, metadataAmount, savedGames, level, gameName);
                
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

