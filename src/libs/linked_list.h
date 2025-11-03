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

LinkedList* list_creater();


#endif