#ifndef ENTITY_H
#define ENTITY_H

#include "core/map.h"
#include <raylib.h>

//Entidades do jogo
typedef enum {
  ENTITY_PLAYER,
  ENTITY_BOMB,
  ENTITY_EXPLOSION_TILE,
  ENTITY_POWER_UP,
  ENTITY_ENEMY,
} EntityType;

//Prioridade de sobreposição de entidades
typedef enum {
  LAYER_PLAYERS,
  LAYER_ENEMIES,
  LAYER_BOMBS,
  LAYER_POWER_UPS
} EntityLayer;

//Direção de possiveis movimentações de uma entidade
typedef enum {
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT,
} EntityDirection;

// Estrutura base para qualquer entidade do jogo
typedef struct Entity {
  EntityType type;
  EntityLayer layer;
  EntityDirection direction;
  Vector2 position;
  float width;
  float height;
  float spawn_time;
  float height_tolerance;

  void (*update)(struct Entity *self);
  void (*draw)(struct Entity *self);
  void (*debug)(struct Entity *self);
} Entity;

Vector2 entity_grid_to_world(Entity *entity, GridPosition grid); // alinha uma entidade ao centro do grid position
GridPosition entity_world_to_grid(Entity *entity); // Recebe uma entidade e retorna a seu grid position em relação a sua posição em pixel

#endif
