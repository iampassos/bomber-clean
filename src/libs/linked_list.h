#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "core/map.h"
#include <stdlib.h>

typedef struct Node{
    void *data;
    struct Node *next;
}Node;

typedef struct{
    Node *head;
}LinkedList;

LinkedList* list_creater(); //criar uma lista
void list_insert_end(LinkedList *list,void *data); //inserir um no no final
int list_lenght(LinkedList *list);

#endif