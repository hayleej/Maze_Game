/*
 * File Name: game.c
 * Author: Haylee Jackson
 * Purpose: All functions related to the game features
 * Last Modified: 09/10/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


char playGame(char *** map, int mapRow, int mapCol, MapObject * player, MapObject * enemy, MapObject * goal)
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
        else if (command != EXIT_GAME)
        {
            pFunction = controlFunc( command );
            if ( pFunction != NULL )
            {
                save( undoList, *map, mapRow, mapCol, *player, *enemy ); 
                (*pFunction)( *map, player, enemy ); /* moves player */
            }
        }
    } while ( !( ( player->row == goal->row ) && ( player->col == goal->col ) ) && !( ( player->row == enemy->row ) && ( player->col == enemy->col ) ) && (command != EXIT_GAME)); /*game is not won and not lost */

    if ( ( player->row == goal->row ) && ( player->col == goal->col ) )
    {
        /* won game */
        command = WON_GAME;
    }
    else if (( player->row == enemy->row ) && ( player->col == enemy->col ))
    {
        /* lost game */
        command = LOST_GAME;
    }
    
    
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
        sPtr = fgets(saved_map_name, sizeof(char)*25, stdin);
        if ( sPtr == NULL )
        {
            if (ferror(stdin))
            {
                perror("Error reading name of saved game\n");
            }
            
        }
        else
        {
            saved_map_name[strcspn(saved_map_name, "\n")] = 0; /* Remove the newline character if present */
            
            printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]\n", saved_map_name);

            disableBuffer();
            scanf( " %c", &option );
            enableBuffer();
        }
    } while ((option != 'y') && (option != EXIT_GAME)); /* until confirmed name or 0 used to exit */
    
    if (option == EXIT_GAME)
    {
        /* making sure it is still NULL */
        free(saved_map_name);
        saved_map_name = NULL;
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
        scanf( " %c", &option );
        if ((option != 'y') && (option != 'n' ))
        {
            /* print error */
            printf("ERROR: %c is an invalid option. Please select y or n.\n",option);
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
                printf("Confirm the saved game name: \033[1m%s\033[0m? [y/n]\n", game->name);

                disableBuffer();
                scanf( " %c", &option );
                enableBuffer();
            } while ((option != 'y') && (option != 'n') && (option != EXIT_GAME)); /* until confirmed name or 0 used to exit */

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
        
        if ((saved_map_name != NULL) && (option != EXIT_GAME))
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

/**
 * @brief  prints the map to the terminal
 * @note   From UCP Assignment 1, but has been edited
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @retval None
 */
void printMap( char ** map, int mapRow, int mapCol )
{ 
    /* variable declarations */
    int i, j;
    char* line = (char *) malloc( sizeof(char) * mapCol ) ;

    system( "clear" );
    printTitle(mapCol+2);
    /* print map with for loop */
    for ( i = 0; i < mapRow; i++ )
    { 
        for ( j = 0; j < mapCol; j++ )
        { 
            line[j] = map[i][j];
        }
        
        printLine( line, mapCol + 2); /* mapCol + 2 so that there is space on either side of the map*/   
    }
    printBorder(mapCol+2);
    printExitCommandInfo(mapCol+2);
    free(line);
}





/**
 * @brief  processes the user's input to move the player
 * @param  command: user's input
 * @retval a pointer to a function that moves the player in the direction specified by the command
 */
CommandPtr controlFunc( char command )
{
    CommandPtr option = NULL;

    if ( command == 'w' )
    {
        option = &up;
    }
    else if ( command == 's' )
    {
        option = &down;
    }
    else if ( command == 'a' )
    {
        option = &left;
    }
    else if ( command == 'd' )
    {
        option = &right;
    }

    return option;
}






/**
 * @brief  moves the player up 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void up( char ** map, MapObject * player, MapObject * enemy )
{
    /* move up */
    if ( ( map[player->row - 1][player->col] == ' ' ) || ( map[player->row - 1][player->col] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->row = player->row - 1;
        map[player->row][player->col] = '^';
        player->obj = '^';
    }
    moveEnemy(map, enemy, player);
}






/**
 * @brief  moves the player down 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void down( char ** map, MapObject * player, MapObject * enemy )
{
    /* move down */
    if ( ( map[player->row + 1][player->col] == ' ' ) || ( map[player->row + 1][player->col] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->row = player->row + 1;
        map[player->row][player->col] = 'v';
        player->obj = 'v';
    }
    moveEnemy(map, enemy, player);
}






/**
 * @brief  moves the player left 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void left( char ** map, MapObject * player, MapObject * enemy )
{
    /* move left */
    if ( ( map[player->row][player->col - 1] == ' ' ) || ( map[player->row][player->col - 1] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->col = player->col - 1;
        map[player->row][player->col] = '<';
        player->obj = '<';
    }
    moveEnemy(map, enemy, player);
}







/**
 * @brief  moves the player right 
 * @note   From UCP Assignment 1 where it was a part of movePlayer() function, but has now been edited into its own function
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void right( char ** map, MapObject * player, MapObject * enemy )
{
    /* move right */
    if ( ( map[player->row][player->col + 1] == ' ' ) || ( map[player->row][player->col + 1] == 'x' ) )
    { 
        map[player->row][player->col] = ' ';
        player->col = player->col + 1;
        map[player->row][player->col] = '>';
        player->obj = '>';
    }
    moveEnemy(map, enemy, player);
}







/**
 * @brief  undo feature to undo previous move
 * @param  undoList: linked list containing past moves in game
 * @param  map: map of the maze
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @param  mapRow: the number of rows in map
 * @retval None
 */
void undo( LinkedList * undoList, char *** map, MapObject * player, MapObject * enemy, int mapRow )
{
    SavedMove * prevMove = NULL;

    if ( undoList->count != 0 )
    {
        prevMove = (SavedMove *)removeStart( undoList );
        freeMap( *map, mapRow ); /* free memory of current map */
        *map = prevMove->sMap;
        *player = prevMove->sPlayer;
        *enemy = prevMove->sEnemy;
        free( prevMove );
    }
}





/**
 * @brief  copies map to saveMap
 * @param  saveMap: where the map is being copied to
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @retval None
 */
void copy( char ** saveMap, char ** map, int mapRow, int mapCol )
{
    int i;
    for ( i = 0; i < mapRow ; i++ )
    { 
        memcpy( saveMap[i], map[i], sizeof(char) * mapCol );
    }
}






/**
 * @brief  saves the current move to the undoList 
 * @param  undoList: linked list containing past moves in game
 * @param  map: map of maze
 * @param  mapRow: number of rows in map
 * @param  mapCol: number of columns in map
 * @param  player: symbol and location of player in map
 * @param  enemy: symbol and location of enemy in map
 * @retval None
 */
void save( LinkedList * undoList, char ** map, int mapRow, int mapCol, MapObject player, MapObject enemy )
{
    SavedMove * move;
    char ** saveMap = initializeMap( mapRow, mapCol );
    copy( saveMap, map, mapRow, mapCol ); 
    move  = (SavedMove *) malloc( sizeof(SavedMove) ); 

    move->sMap = saveMap; 
    move->sPlayer = player; 
    move->sEnemy = enemy; 
    insertStart( undoList, move );
}




/**
 * @brief  frees the maps in the past moves in the undoList
 * @param  undoList: linked list containing past moves in game
 * @param  mapRow: number of rows in map
 * @retval None
 */
void freeSavedMap( LinkedList * undoList, int mapRow )
{
    LinkedListNode * pCur = undoList->head;
    LinkedListNode * pTemp = NULL;
    SavedMove * saved = NULL;

    while ( pCur )
    {
        pTemp = pCur->next;

        /* free pCur's savedMove map */
        saved = (SavedMove *)pCur->data;
        freeMap( saved->sMap, mapRow );

        pCur = pTemp;
    }
}
