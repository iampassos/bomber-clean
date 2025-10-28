#include "bomb.h"

void create_bombs_list(Bombs *list) {
  list->head = NULL;
  list->tail = NULL;
  list->currentLength = 0;
  list->totalCreated = 0;
}

// insersão no final de uma bomba
void insert_bomb(Bombs *list, Vector2 posi) {
  Bomb *newBomb = malloc(sizeof(Bomb));
  if (newBomb == NULL)
    return;

  list->totalCreated++;
  list->currentLength++;
  newBomb->posi = posi;
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
void remove_bomb(Bombs *list) {
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
bool remove_node_bomb(Bombs *list,Bomb *node){
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



void free_list(Bombs *list) {
  if (list != NULL && list->head != NULL) {
    while (list->head != NULL)
      remove_bomb(list);
    list->currentLength = 0;
    list->totalCreated = 0;
  }
}

bool is_possible_insert_bomb_in_map(Bombs *list, Vector2 spawn_posi,
                                    TileType tile) {
  if (tile != TILE_EMPTY)
    return false;
  if (list != NULL && list->head != NULL) {
    Bomb *current = list->head;
    do {
      if (spawn_posi.x == current->posi.x && spawn_posi.y == current->posi.y)
        return false;
      current = current->next;
    } while (current != list->head);
  }
  return true;
}

Bomb *find_bomb_to_explode(Bombs *list){
    if(list ==NULL || list->head ==NULL) return NULL;

    Bomb *current=list->head;
    do{
        if(GetTime()- current->spawnTime >= EXPLODE_DELAY) return current;
        current=current->next;
    }while(current!=list->head);

    return NULL;
}


// -- funcão que não sei se iremos usar --

void increase_time_to_explode_bombs(Bombs *list){
    if(list ==NULL || list->head ==NULL) return;
    Bomb *current=list->head;

    do{
      current->spawnTime+=PLUS_EXPLODE_DELAY;
      current=current->next;
    }while(current!=list->head);

}