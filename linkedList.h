/*
 * File Name: linkedList.h
 * Author: Haylee Jackson
 * Purpose: header file for linkedList.c
 * Last Modified: 09/10/2021
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

typedef void(*listFunc)(void* data);

typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct LinkedList
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;

} LinkedList;

LinkedList* createLinkedList();
void insertStart( LinkedList * list, void * value );
void* removeStart( LinkedList * list );
void insertLast( LinkedList* list, void* value );
void* removeLast( LinkedList* list );
void printLinkedList( LinkedList* list, listFunc funcPtr );
void* freeNode( LinkedListNode* node );
void freeLinkedList( LinkedList* list, listFunc funcPtr );

#endif
