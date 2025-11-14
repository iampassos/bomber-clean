#ifndef BOMB_H
#define BOMB_H

#include "core/animation.h"
#include "core/map.h"
#include "entities/entity.h"

typedef struct {
  Entity entity;
  int player_id;
  bool exploded;
  int radius;
  float explosion_time;
  Animation tick_animation;
  Animation spawn_animation;
} Bomb;

Bomb *bomb_create(int player_id, Vector2 position, int radius); //Construtor de uma entidade bomba

void bomb_update(Entity *self); //Lida com toda a física de atualização de uma bomba do jogo
void bomb_draw(Entity *self); 

Bomb *bomb_at_grid(GridPosition grid); //Verifica se existe uma bomba em um grid position

#endif
