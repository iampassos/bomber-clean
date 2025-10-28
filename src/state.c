#include "state.h"
#include "bomb.h"
#include "common.h"
#include "map.h"
#include "player.h"

State state;

void state_init() {
  map_init();

  player_new(0, map_get_vector_from_grid((GridPosition){1, 1}), TILE_SIZE - 6,
             TILE_SIZE - 6);

  for (int i = 0; i < MAX_PLAYERS; i++)
    bombs_create_list(&state.bombs[i]);

  state.view_mode = DEBUG;
}
