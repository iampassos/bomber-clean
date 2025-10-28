#include "state.h"
#include "common.h"
#include "map.h"
#include "player.h"

State state;

void state_init() {
  map_init();

  player_new(0, map_get_vector_from_grid((GridPosition){1, 1}), TILE_SIZE - 6,
             TILE_SIZE - 6);

  state.view_mode = DEBUG;
}
