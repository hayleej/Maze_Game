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
    CommandPtr pFunction;
    LinkedList * undoList = NULL; 
    char errorLevelMessage[52];
    

    if ( argc == 2 )
    { 
        undoList = createLinkedList(); 
        
        do
        { 
            /* display start screen */
            printStartScreen(errorLevelMessage, MIN_LENGTH);
            disableBuffer();
            /* select map option*/
            scanf( " %c", &option );
            strcpy(errorLevelMessage, "ERROR: x is an invalid option. Please select 1 or 2");
            errorLevelMessage[7] = option;
        } while ( !((option == '1') || (option == '2' ) || (option == '0' )) ); /* correct option has not been selected */

        enableBuffer();

        if (option == '2')
        {
            /* enter custom map path */
            system( "clear" );
            printTitle(MIN_LENGTH);
            do
            {
                printf("Enter path to custom map:\n");
                /* select path to custom map */
                fgets(map_path, sizeof(map_path), stdin);
                map_path[strcspn(map_path, "\n")] = 0; /* Remove the newline character if present */
                if (strcmp(map_path,"0") != 0)
                {
                    /* so to not print error opening file when trying to exit */
                    map = readFile( map_path, &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
                }
                
            } while ((map == NULL) && (strcmp(map_path,"0") != 0)); /* until map_path is correct or 0 is used to exit */
            
            
        }
        else
        {   
            map = readFile( argv[1], &mapRow, &mapCol, &player, &enemy, &goal, &metadataAmount );
        }
        

        if ((map != NULL) && (option != '0')) /* user hasn't exited game */
        {
            /* map has been initialized */
            do
            { 
                printMap( map, mapRow, mapCol );

                disableBuffer();
                scanf( " %c", &command );
                
                if ( command == 'u' )
                {
                    undo( undoList, &map, &player, &enemy, mapRow );
                }
                else if (command != '0')
                {
                    pFunction = controlFunc( command );
                    if ( pFunction != NULL )
                    {
                        save( undoList, map, mapRow, mapCol, player, enemy ); 
                        (*pFunction)( map, &player, &enemy ); /* moves player */
                    }
                }
            } while ( !( ( player.row == goal.row ) && ( player.col == goal.col ) ) && !( ( player.row == enemy.row ) && ( player.col == enemy.col ) ) && (command != '0')); /*game is not won and not lost */

            enableBuffer();
            
            if (command == '0')
            {
                /* exiting game */
                printf( "Exiting game...\n" );
                
                do
                { 
                    /* save progress prompt */
                    printf( "Do you want to save your progress? [y/n]\n" );
                    scanf( " %c", &option );
                    if ((option != 'y') && (option != 'n' ))
                    {
                        /* print error */
                        printf("ERROR: %c is an invalid option. Please select y or n",option);
                    }
                
                } while ( !((option == 'y') || (option == 'n' ) )); /* correct option has not been selected */

                if (option == 'y')
                {
                    /* save progress */
                    writeSaveFile( "map.out", map, mapRow, mapCol, metadataAmount);
                }
                
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
            
            /* free malloced memory */
            freeSavedMap( undoList, mapRow );
        }
        
        /* free malloced memory */
        freeLinkedList( undoList, &free );
        free( undoList );
        freeMap( map, mapRow );
    }
    else
    { 
        /* Error when number of command line arguments is not equal to 2 */
        printf( "Error: Not the right number of arguements in the command line." );
    }
    return 0;
}
