#include "explosion.h"
#include "entities_manager.h"
#include "game/game_manager.h"
#include <stdlib.h>

//    GridPosition affected[4 * GRID_WIDTH];
//     GridPosition destroyed[4 * GRID_WIDTH];
//     int affected_lenght;
//     int destroyed_lenght;

Explosion *explosion_create(int radius, Vector2 position) {
  Entity entity;
  entity.type = ENTITY_EXPLOSION;
  entity.layer = LAYER_BOMBS; // Camada de apresentacao
  entity.position = position;
  entity.width = TILE_SIZE; // tamanho do desenho da animacao
  entity.height = TILE_SIZE;
  entity.update = NULL;
  entity.draw = NULL;
  entity.debug = NULL;

  Explosion *explosion = malloc(sizeof(Explosion));
  explosion->entity = entity;
  explosion->radius = radius;
  explosion->affected_length = 0;
  explosion->destroyed_length = 0;

  // Dar dano em que precisa
  //  Destruir os blocos
  game_manager_on_bomb_exploded(explosion);

  //   entities_manager_add((Entity *)explosion);

  return explosion;
}