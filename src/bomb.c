#include "bomb.h"
#include "map.h"
#include "state.h"
#include <raylib.h>

void bombs_create_list(Bombs *list) {
  list->head = NULL;
  list->tail = NULL;
  list->currentLength = 0;
  list->totalCreated = 0;
}

// insersão no final de uma bomba
void bomb_insert(Bombs *list, GridPosition pos) {
  Bomb *newBomb = malloc(sizeof(Bomb));
  if (newBomb == NULL)
    return;
  list->totalCreated++;
  list->currentLength++;
  newBomb->grid_position = pos;
  newBomb->spawnTime = GetTime();
  newBomb->animation_step = 0;
  newBomb->last_animation_step = 0;
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

// remosão de um no especifico
bool bomb_node_remove(Bombs *list, Bomb *node) {
  if (node == NULL || list == NULL || list->head == NULL)
    return false;
  Bomb *current = list->head;
  do {
    if (current == node) {
      // Check de um no
      if (list->head == list->tail)
        list->head = list->tail = NULL;
      else {
        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (node == list->head)
          list->head = node->next;
        if (node == list->tail)
          list->tail = node->prev;
      }
      list->currentLength--;
      free(node);
      return true;
    }
    current = current->next;
  } while (current != list->head);
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

bool bomb_is_possible_insert_in_map(Bombs *list, GridPosition pos,
                                    TileType tile) {
  if (tile != TILE_EMPTY)
    return false;
  if (list != NULL && list->head != NULL) {
    Bomb *current = list->head;
    do {
      if (pos.col == current->grid_position.col &&
          pos.row == current->grid_position.row)
        return false;
      current = current->next;
    } while (current != list->head);
  }
  return true;
}

Bomb *bomb_find_n(Bombs *list, int n) {
  if (list == NULL || list->head == NULL)
    return NULL;

  Bomb *current = list->head;
  int i = 0;
  do {
    if (i == n)
      return current;
    current = current->next;
    i++;
  } while (current != list->head);

  return NULL;
}

Bomb *bomb_find_on_grid_position(GridPosition pos) {
  for (int i = 0; i < state.player_count; i++) {
    Bombs *bombs = &state.bombs[i];
    for (int j = 0; j < bombs->currentLength; j++) {
      Bomb *bomb = bomb_find_n(bombs, j);
      if (bomb->grid_position.col == pos.col &&
          bomb->grid_position.row == pos.row)
        return bomb;
    }
  }

  return NULL;
}

Bomb *bomb_find_to_explode(Bombs *list) {
  if (list == NULL || list->head == NULL)
    return NULL;

  Bomb *current = list->head;
  do {
    if (GetTime() - current->spawnTime >= EXPLODE_DELAY)
      return current;
    current = current->next;
  } while (current != list->head);

  return NULL;
}

void bombs_increase_time_to_explode(Bombs *list) {
  if (list == NULL || list->head == NULL)
    return;
  Bomb *current = list->head;

  do {
    current->spawnTime += PLUS_EXPLODE_DELAY;
    current = current->next;
  } while (current != list->head);
}

void bombs_update_all() {
  for (int i = 0; i < state.player_count; i++) {
    Bombs *bombs = &state.bombs[i];
    for (int j = 0; j < bombs->currentLength; j++) {
      Bomb *bomb = bomb_find_n(bombs, j);
      if (GetTime() - bomb->spawnTime >= EXPLODE_DELAY)
        bomb_node_remove(bombs, bomb);
      if (GetTime() - bomb->last_animation_step >= EXPLODE_DELAY / 10.0f) {
        bomb->animation_step = (bomb->animation_step + 1) % 3;
        bomb->last_animation_step = GetTime();
      }
    }
  }
}
