#include "bomb.h"

void bombs_create_list(Bombs *list) {
  list->head = NULL;
  list->tail = NULL;
  list->currentLength = 0;
  list->totalCreated = 0;
}

// insersão no final de uma bomba
void bomb_insert(Bombs *list, int col, int row) {
  Bomb *newBomb = malloc(sizeof(Bomb));
  if (newBomb == NULL)
    return;
  list->totalCreated++;
  list->currentLength++;
  newBomb->col=col;
  newBomb->row=row;
  newBomb->spawnTime = GetTime();
  newBomb->next = NULL;

  // insersão com um elemento
  if (list->head == NULL) {
    newBomb->next = newBomb->prev = newBomb;
    list->head = list->tail = newBomb;
  } else {
    list->tail->next = newBomb;
    newBomb->prev = list->tail;
    list->tail = newBomb;
    newBomb->next = list->head;
    list->head->prev = newBomb;
  }
}

// remosao no final de bomba
void bomb_remove(Bombs *list) {
  if (list == NULL || list->head == NULL)
    return;

  list->currentLength--;
  Bomb *delete = list->tail;

  if (list->head == list->tail)
    list->head = list->tail = NULL;
  else {
    list->tail = list->tail->prev;
    list->tail->next = list->head;
    list->head->prev = list->tail;
  }
  free(delete);
}

//remosão de um no especifico
bool bomb_node_remove(Bombs *list,Bomb *node){
    if(node == NULL || list == NULL || list->head == NULL) return false;
    Bomb *current = list->head;
    do{
        if(current==node){
            //Check de um no
            if(list->head==list->tail) list->head=list->tail=NULL;
            else{
                node->prev->next=node->next;
                node->next->prev=node->prev;

                if(node == list->head) list->head = node->next;
                if(node == list->tail) list->tail = node->prev;
            }
            list->currentLength--;
            free(node);
            return true;
        }
        current=current->next;
    }while(current!=list->head);
    return false;
    
}



void bomb_free_list(Bombs *list) {
  if (list != NULL && list->head != NULL) {
    while (list->head != NULL)
      bomb_remove(list);
    list->currentLength = 0;
    list->totalCreated = 0;
  }
}

bool bomb_is_possible_insert_in_map(Bombs *list,int col, int row,
                                    TileType tile) {
  if (tile != TILE_EMPTY)
    return false;
  if (list != NULL && list->head != NULL) {
    Bomb *current = list->head;
    do {
      if (col== current->col && row == current->row)
        return false;
      current = current->next;
    } while (current != list->head);
  }
  return true;
}

Bomb *bomb_find_to_explode(Bombs *list){
    if(list ==NULL || list->head ==NULL) return NULL;

    Bomb *current=list->head;
    do{
        if(GetTime()- current->spawnTime >= EXPLODE_DELAY) return current;
        current=current->next;
    }while(current!=list->head);

    return NULL;
}


// -- funcão que não sei se iremos usar --

void bombs_increase_time_to_explode(Bombs *list){
    if(list ==NULL || list->head ==NULL) return;
    Bomb *current=list->head;

    do{
      current->spawnTime+=PLUS_EXPLODE_DELAY;
      current=current->next;
    }while(current!=list->head);

}