#include "player.h"
#include "core/animation.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "entities/bomb.h"
#include "entities/entities_manager.h"
#include "entity.h"
#include "game/game_manager.h"
#include "game/rules.h"
#include "input/input_manager.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT_TOLERANCE 28.5f

Vector2 player_grid_to_world(Player *player, GridPosition grid) {
  Vector2 center = map_grid_to_world_center(grid);
  return (Vector2){center.x - player->entity.width / 2,
                   center.y - player->entity.height / 2 - HEIGHT_TOLERANCE};
}

GridPosition player_world_to_grid(Player *player) {
  Vector2 feet_position =
      (Vector2){player->entity.position.x + player->entity.width / 2.0f,
                player->entity.position.y +
                    (player->entity.direction == DIR_UP
                         ? player->entity.height * 1.1f
                         : player->entity.height * 0.60f + HEIGHT_TOLERANCE)};
  GridPosition pos = map_world_to_grid(feet_position);
  return pos;
}

Player *player_create(int id, Vector2 position) {
  Entity entity;
  entity.type = ENTITY_PLAYER;
  entity.layer = LAYER_PLAYERS;
  entity.direction = DIR_DOWN;
  entity.position = position;
  entity.width = TILE_SIZE - 10;
  entity.height = TILE_SIZE - 10;
  entity.spawn_time = GetTime();
  entity.update = player_update;
  entity.draw = player_draw;
  entity.debug = player_debug;

  Player *player = malloc(sizeof(Player));
  player->entity = entity;
  player->id = id;
  player->alive = true;
  player->invencible = true;
  player->invencibility_start = GetTime();
  player->lives = PLAYER_DEFAULT_LIVES;
  player->bomb_capacity = DEFAULT_BOMBS;
  player->bomb_radius = DEFAULT_BOMB_RADIUS;
  player->speed = PLAYER_DEFAULT_SPEED;
  player->input = (PlayerInput){{0}, false};

  animation_init(&player->death_animation, 7, 0.3f, false, false);
  animation_init(&player->walk_animation, 3, 0.25f, true, false);
  animation_play(&player->walk_animation);
  animation_init(&player->invencible_animation, 2, 0.1f, true, false);
  animation_play(&player->invencible_animation);

  GridPosition pos = map_world_to_grid(position);
  pos.col = fmax(1, fmin(pos.col, GRID_WIDTH - 2));
  pos.row = fmax(1, fmin(pos.row, GRID_HEIGHT - 2));

  Map *map = &game_manager.map;

  entities_manager_add((Entity *)player);

  if (map_is_walkable(map, pos)) {
    player->entity.position = player_grid_to_world(player, pos);
    return player;
  }

  for (int r = pos.col; r < GRID_HEIGHT - 1; r++) {
    for (int c = pos.row; c < GRID_WIDTH - 1; c++) {
      if (map_is_walkable(map, (GridPosition){r, c})) {
        player->entity.position =
            player_grid_to_world(player, (GridPosition){c, r});
        return player;
      }
    }
  }

  player->entity.position = player_grid_to_world(player, (GridPosition){1, 1});

  return player;
}

void player_update(Entity *self) {
  Player *player = (Player *)self;

  if (!player->alive) {
    if (!animation_is_playing(&player->death_animation) &&
        !animation_ended(&player->death_animation)) {
      animation_play(&player->death_animation);
    } else if (!animation_ended(&player->death_animation)) {
      animation_update(&player->death_animation);
    } else {
      player->lives--;

      if (player->lives <= 0)
        entities_manager_remove(self);
      else {
        player->alive = true;
        animation_stop(&player->death_animation);
        player->entity.position =
            player_grid_to_world(player, (GridPosition){1, 1});
      }
    }

    return;
  }

  if (GetTime() - player->invencibility_start >= PLAYER_INVENCIBILITY_TIME) {
    animation_stop(&player->invencible_animation);
    player->invencible = false;
  } else {
    if (animation_is_playing(&player->invencible_animation))
      animation_update(&player->invencible_animation);
    else
      animation_play(&player->invencible_animation);
  }

  if (player->input.place_bomb && rules_can_place_bomb(player))
    bomb_create(player->id, map_grid_to_world(player_world_to_grid(player)),
                player->bomb_radius);

  Vector2 projected = player->entity.position;

  projected.x = fmax(MAP_X_OFFSET, player->entity.position.x +
                                       player->speed * player->input.move.x);
  projected.y = fmax(MAP_Y_OFFSET, player->entity.position.y +
                                       player->speed * player->input.move.y);

  Vector2 new_pos = player->entity.position;

  Vector2 horizontal = {projected.x,
                        player->entity.position.y + HEIGHT_TOLERANCE};
  if (physics_can_move_to(horizontal, player->entity.width,
                          player->entity.height))
    new_pos.x = horizontal.x;

  Vector2 vertical = {player->entity.position.x, projected.y};
  if (physics_can_move_to((Vector2){vertical.x, vertical.y + HEIGHT_TOLERANCE},
                          player->entity.width, player->entity.height))
    new_pos.y = vertical.y;

  float dx = new_pos.x - player->entity.position.x;
  float dy = new_pos.y - player->entity.position.y;

  if (fabs(dx) > fabs(dy)) {
    player->entity.direction = dx > 0 ? DIR_RIGHT : DIR_LEFT;
    player->state = STATE_RUNNING;
  } else if (fabs(dy) > 0.0f) {
    player->entity.direction = dy > 0 ? DIR_DOWN : DIR_UP;
    player->state = STATE_RUNNING;
  } else if (fabs(dy) == 0.0f && fabs(dx) == 0.0f) {
    player->state = STATE_IDLE;
  }

  if (player->state == STATE_RUNNING) {
    animation_update(&player->walk_animation);
    animation_play(&player->walk_animation);
  } else {
    player->walk_animation.current_frame = 1;
    animation_pause(&player->walk_animation);
  }

  player->entity.position = new_pos;
}

void player_draw(Entity *self) {
  Player *player = (Player *)self;

  if (animation_is_playing(&player->death_animation)) {
    Texture2D *texture = asset_manager_get_player_death_texture(
        animation_get_frame(&player->death_animation));

    DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
                WHITE);
  } else {
    int frame = animation_get_frame(&player->invencible_animation);

    Texture2D *texture =
        frame == 1 ? asset_manager_get_player_walk_white_texture(
                         player->entity.direction, frame)
                   : asset_manager_get_player_walk_texture(
                         player->entity.direction,
                         animation_get_frame(&player->walk_animation));

    DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
                WHITE);
  }
}

void player_debug(Entity *self) {
  Player *player = (Player *)self;

  GridPosition pos = player_world_to_grid(player);
  TileType tile = map_get_tile(&game_manager.map, pos);
  char strBuffer[1000];
  snprintf(strBuffer, sizeof(strBuffer),
           "Player debug\n"
           "id: %d\n"
           "position: (%.2f, %.2f)\n"
           "grid: (%d, %d)\n"
           "width: %.2f\n"
           "height: %.2f\n"
           "direction: %s\n"
           "state: %s\n"
           "bomb-capacity: %d\n"
           "bombs: %d\n"
           "bomb-radius: %d\n"
           "speed: %.2f\n"
           "invencible: %s\n"
           "alive: %s\n"
           "lives: %d\n"
           "animation-step: %d\n"
           "standing-on: %s",
           player->id, player->entity.position.x, player->entity.position.y,
           pos.col, pos.row, player->entity.width, player->entity.height,
           player->entity.direction == DIR_UP     ? "UP"
           : player->entity.direction == DIR_DOWN ? "DOWN"
           : player->entity.direction == DIR_LEFT ? "LEFT"
                                                  : "RIGHT",
           player->state == STATE_IDLE      ? "IDLE"
           : player->state == STATE_RUNNING ? "RUNNING"
                                            : "DEAD",
           player->bomb_capacity, player_get_all_bombs(player, NULL),
           player->bomb_radius, player->speed,
           player->invencible ? "yes" : "no", player->alive ? "yes" : "no",
           player->lives, player->walk_animation.current_frame,
           tile == TILE_EMPTY   ? "EMPTY"
           : tile == TILE_WALL  ? "WALL"
           : tile == TILE_BRICK ? "BRICK"
                                : "BOMB");

  Vector2 textSize = MeasureTextEx(GetFontDefault(), strBuffer, 20, 1.0f);

  float x = 15;
  float y = SCREEN_HEIGHT / 2.0f - textSize.y / 2.0f;

  DrawRectangle(x, y, textSize.x + 10, textSize.y + 10,
                (Color){196, 196, 196, 200});

  DrawTextEx(GetFontDefault(), strBuffer, (Vector2){x, y}, 20, 1.0f, BLACK);

  Vector2 grid = map_grid_to_world(pos);

  DrawRectangle(grid.x, grid.y, TILE_SIZE, TILE_SIZE,
                (Color){128, 128, 128, 128});
}

int player_get_all_bombs(Player *player, Entity **out) {
  int count = 0;
  for (int i = 0; i < MAX_ENTITIES && count <= player->bomb_capacity; i++) {
    Entity *entity = entities_manager.entries[i];

    if (entity == NULL)
      break;

    Bomb *bomb = (Bomb *)entity;

    if (entity->type == ENTITY_BOMB && bomb->player_id == player->id) {
      if (out != NULL)
        out[count] = entity;
      count++;
    }
  }

  return count;
}

Player *player_on_grid(GridPosition grid) {
  for (int i = 0; i < game_manager.player_count; i++) {
    Player *player = (Player *)game_manager.players[i];

    GridPosition grid2 = player_world_to_grid(player);

    if (map_is_same_grid(grid, grid2))
      return player;
  }

  return NULL;
}
