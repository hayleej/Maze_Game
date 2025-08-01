/*
 * File Name: linkedList.c
 * Author: Haylee Jackson
 * Purpose: All functions related to generic Linked List
 * Last Modified: 09/10/2021
*/

#include <stdlib.h>
#include "linkedList.h"


/**
 * @brief  creates the linked list
 * @retval linked list
 */
LinkedList* createLinkedList()
{
    LinkedList * pLinkedList = (LinkedList *) malloc( sizeof(LinkedList) );
    pLinkedList->head = NULL;
    pLinkedList->tail = NULL;
    pLinkedList->count = 0;
    
    return pLinkedList;
}





/**
 * @brief  inserts node at start of linked list
 * @param  list: linked list
 * @param  value: data of new node
 * @retval None
 */
void insertStart( LinkedList * list, void * value )
{
    LinkedListNode * pNode = (LinkedListNode *) malloc( sizeof(LinkedListNode) );
    pNode->data = value;
    pNode->next = NULL;

    if ( list->tail == NULL )
    {
        /* no nodes in list */
        list->tail = pNode;
        list->count = 1;
    }
    else
    {
        pNode->next = list->head;
        (list->count)++;
    }
    list->head = pNode;
}







/**
 * @brief  removes the first node in linked list
 * @param  list: linked list
 * @retval data of removed node
 */
void* removeStart( LinkedList * list )
{
    void * pData = NULL;
    LinkedListNode * pNext;
    pData = list->head->data;

    if ( list->count == 1 )
    {
        /* one node in list */
        pData = freeNode( list->head );
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        pNext = list->head->next;
        pData = freeNode( list->head );
        list->head = pNext;
        pNext = NULL;
    }
    
    (list->count)--;

    return pData;
}






/**
 * @brief  insert node at end of linked list
 * @param  list: linked list
 * @param  value: data of new node
 * @retval None
 */
void insertLast( LinkedList * list, void * value )
{
    LinkedListNode * pNode = (LinkedListNode *) malloc( sizeof(LinkedListNode) );
    pNode->data = value;
    pNode->next = NULL;

    if ( list->head == NULL )
    {
        /* no nodes in list */
        list->head = pNode;
        list->count = 1;
    }
    else
    {
        list->tail->next = pNode;
        (list->count)++;
    }
    list->tail = pNode;
}







/**
 * @brief  removes the last node in linked list
 * @param  list: linked list
 * @retval data of removed node
 */
void* removeLast( LinkedList * list )
{
    void * pData = NULL;
    LinkedListNode * pCur = list->head;
    
    while ( pCur )
    {
        if ( list->count == 1 )
        {
            /* one node in list */
            pData = freeNode( list->tail );
            list->tail = NULL;
            free( list->head );
            list->head = NULL;
        }
        else if ( pCur->next == list->tail )
        {
            pData = freeNode( list->tail );
            pCur->next = NULL;
            list->tail = pCur;
            pCur = NULL;
        }
        else
        {
            pCur = pCur->next;
        }
    }
    
    (list->count)--;

    return pData;
}





/**
 * @brief  print the linked list
 * @param  list: linked list
 * @param  funcPtr: a pointer to a function that prints nodes data (void *)
 * @retval None
 */
void printLinkedList( LinkedList * list, listFunc funcPtr )
{
    LinkedListNode * pCur = list->head;

    while ( pCur )
    {
        (*funcPtr)(pCur->data);
        pCur = pCur->next;
    } /* traverse the linked list */
}









/**
 * @brief  frees memory of linked list node
 * @param  node: node to free
 * @retval data of node that was freed
 */
void* freeNode( LinkedListNode * node )
{
    void * pData = NULL;

    pData = node->data;
    node->data = NULL;
    free( node );

    return pData;
}







/**
 * @brief  frees memory of linked list
 * @param  list: linked list
 * @param  funcPtr: a pointer to a function that frees node's data (void *)
 * @retval None
 */
void freeLinkedList( LinkedList * list, listFunc funcPtr )
{
    LinkedListNode * pCur = list->head;
    LinkedListNode * pTemp = NULL;

    while ( pCur ) 
    {
        pTemp = pCur->next;

        /* free current node's pData via the function pointer */
        (*funcPtr)(pCur->data);

        pCur->next = NULL;
        pCur->data = NULL;

        /* free current node */
        freeNode( pCur );
        pCur = pTemp;
    }
}

