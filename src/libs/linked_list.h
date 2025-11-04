#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "core/map.h"
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} LinkedList;

LinkedList *list_create();                          // criar uma lista
void list_insert_end(LinkedList *list, void *data); // inserir um no no final
int list_length(LinkedList *list);
void list_free_all(LinkedList *list);
int list_find_node_position(
    LinkedList *list, void *target); // achar a posicao de um data especifico
void *list_get_data_position(LinkedList *list,
                             int posi); // retorna uma data por posicao

void pop(LinkedList *list); //excluir o primeiro no

#endif
