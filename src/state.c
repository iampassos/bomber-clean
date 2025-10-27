#include "state.h"
#include "common.h"
#include "map.h"
#include "player.h"

State state;

void state_init() {
  map_init();

  player_new(0, (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
             TILE_SIZE - 10, TILE_SIZE - 10);
}
