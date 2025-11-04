#include "linked_list.h"

LinkedList *list_create() {
  LinkedList *list = malloc(sizeof(LinkedList));
  if (list == NULL)
    return NULL;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void list_insert_end(LinkedList *list, void *data) {
  if (list == NULL)
    return;

  Node *new = malloc(sizeof(Node));
  if (new == NULL)
    return;
  new->data = data;
  new->next = NULL;

  if (list->head == NULL){
    list->head = new;
    list->tail = new;
  }
  else {
    list->tail->next=new;
    list->tail=new;
  }
}

int list_length(LinkedList *list) {
  if (list == NULL || list->head == NULL)
    return 0;
  else {
    int cont = 0;
    Node *aux = list->head;
    while (aux != NULL) {
      aux = aux->next;
      cont++;
    }
    return cont;
  }
}

void list_free_all(LinkedList *list) {
  if (list == NULL)
    return;

  Node *aux = list->head;
  while (aux != NULL) {
    Node *delete = aux;
    aux = aux->next;
    free(aux->data); // libera o ponteiro data
    free(delete);    // libera o nó em si
  }
  free(list);
}

void pop(LinkedList *list){

  if(list!=NULL && list->head!=NULL){
    Node *delete=list->head;
    list->head=list->head->next;
    free(delete->data);
    free(delete);
    if(list->head==NULL){
      list->tail=NULL;
    }
  }
}


int list_find_node_position(LinkedList *list, void *target) {
  if (list == NULL || target == NULL)
    return -1;

  Node *aux = list->head;
  int posi = 0;

  while (aux != NULL) {
    if (aux->data == target)
      return posi;
    aux = aux->next;
    posi++;
  }
  return -1;
}

void *list_get_data_position(LinkedList *list, int posi) {
  if (list == NULL || list->head == NULL || posi < 0)
    return NULL;

  Node *aux = list->head;
  int cont = 0;

  while (aux != NULL) {
    if (posi == cont)
      return aux->data;
    aux = aux->next;
    cont++;
  }
  return NULL;
}
