#include "player.h"
#include "core/animation.h"
#include "core/assets/assets_players.h"
#include "core/common.h"
#include "core/map.h"
#include "core/physics.h"
#include "core/score.h"
#include "entities/bomb.h"
#include "entities/entities_manager.h"
#include "entities/power_up.h"
#include "entity.h"
#include "game/game_manager.h"
#include "game/rules.h"
#include "input/input_manager.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Player *player_create(int id, GridPosition spawn_grid) {
  spawn_grid.col = fmax(1, fmin(spawn_grid.col, GRID_WIDTH - 2));
  spawn_grid.row = fmax(1, fmin(spawn_grid.row, GRID_HEIGHT - 2));

  Entity entity;
  entity.type = ENTITY_PLAYER;
  entity.layer = LAYER_PLAYERS;
  entity.direction = DIR_DOWN;
  entity.position = (Vector2){0, 0};
  entity.width = TILE_SIZE - 4.5f;
  entity.height = TILE_SIZE - 4.5f;
  entity.spawn_time = GetTime();
  entity.height_tolerance = PLAYER_HEIGHT_TOLERANCE;
  entity.update = player_update;
  entity.draw = player_draw;
  entity.debug = player_debug;

  Player *player = malloc(sizeof(Player));
  player->entity = entity;
  player->id = id;
  player->spawn_grid = spawn_grid;
  player->alive = true;
  player->invencible = true;
  player->invencibility_start = GetTime();
  player->lives = PLAYER_DEFAULT_LIVES;
  player->bomb_capacity = DEFAULT_BOMBS;
  player->bomb_radius = DEFAULT_BOMB_RADIUS;
  player->speed = PLAYER_DEFAULT_SPEED;
  player->input = (PlayerInput){{0}, false};

  player->entity.position = entity_grid_to_world(&player->entity, spawn_grid,
                                                 PLAYER_HEIGHT_TOLERANCE);

  animation_init(&player->death_animation, (int[]){0, 1, 2, 3, 4, 5, 6}, 7,
                 0.3f, false, false);
  animation_init(&player->walk_animation, (int[]){0, 1, 2}, 3, 0.25f, true,
                 true);
  animation_init(&player->invencible_animation, (int[]){0, 1}, 2, 0.1f, true,
                 true);

  Map *map = game_manager.map;

  entities_manager_add((Entity *)player);

  if (map_is_walkable(map, spawn_grid)) {
    player->entity.position = entity_grid_to_world(&player->entity, spawn_grid,
                                                   PLAYER_HEIGHT_TOLERANCE);
    return player;
  }

  for (int r = spawn_grid.col; r < GRID_HEIGHT - 1; r++) {
    for (int c = spawn_grid.row; c < GRID_WIDTH - 1; c++) {
      if (map_is_walkable(map, (GridPosition){r, c})) {
        player->entity.position = entity_grid_to_world(
            &player->entity, (GridPosition){c, r}, PLAYER_HEIGHT_TOLERANCE);
        return player;
      }
    }
  }

  player->entity.position = entity_grid_to_world(
      &player->entity, (GridPosition){1, 1}, PLAYER_HEIGHT_TOLERANCE);

  return player;
}

void player_update(Entity *self) {
  Player *player = (Player *)self;

  if (!player->alive) {
    if (!player->death_animation.playing &&
        !animation_is_finished(&player->death_animation)) {
      animation_play(&player->death_animation);
      return;
    } else if (!animation_is_finished(&player->death_animation)) {
      animation_update(&player->death_animation);
      return;
    }

    player->lives--;

    if (player->lives <= 0) {
      player->death_life_time = GetTime() - game_manager.stage_start;
      score_set_player(player);
      entities_manager_remove(self);
    } else {
      player->alive = true;
      player->invencible = true;
      animation_reset(&player->death_animation);
      player->entity.position = entity_grid_to_world(
          &player->entity, player->spawn_grid, PLAYER_HEIGHT_TOLERANCE);
    }

    return;
  }

  for (int i = 0; i < entities_manager.count; i++) {
    Entity *entity2 = entities_manager.entries[i];
    if (entity2->type == ENTITY_ENEMY &&
        physics_entity_collision(&player->entity, entity2)) {
      game_manager_on_enemy_touch(player, (Enemy *)entity2);
    }
  }

  if (player->invencible) {
    if (!player->invencible_animation.playing) {
      animation_play(&player->invencible_animation);
      player->invencibility_start = GetTime();
    } else if (GetTime() - player->invencibility_start >=
               PLAYER_INVENCIBILITY_TIME) {
      player->invencible = false;
      animation_reset(&player->invencible_animation);
    }
  }

  if (player->input.place_bomb && rules_can_place_bomb(player))
    bomb_create(player->id,
                map_grid_to_world(entity_world_to_grid(
                    &player->entity, PLAYER_HEIGHT_TOLERANCE)),
                player->bomb_radius);

  Vector2 projected = player->entity.position;

  projected.x = fmax(MAP_X_OFFSET, player->entity.position.x +
                                       player->speed * player->input.move.x);

  Vector2 new_pos = player->entity.position;

  Vector2 horizontal = {projected.x,
                        player->entity.position.y + PLAYER_HEIGHT_TOLERANCE};
  if (physics_can_move_to(horizontal, player->entity.width,
                          player->entity.height))
    new_pos.x = horizontal.x;
  else if (player->input.move.y == 0) {
    float offset_in_tile =
        player->entity.direction != DIR_UP
            ? fmod(player->entity.position.y + PLAYER_HEIGHT_TOLERANCE,
                   TILE_SIZE)
            : fmod(player->entity.position.y - PLAYER_HEIGHT_TOLERANCE,
                   TILE_SIZE);

    float dist_to_up = offset_in_tile;
    float dist_to_down = TILE_SIZE - offset_in_tile;
    float dist_from_center = fabs(offset_in_tile - TILE_SIZE / 2.0f);

    if (dist_from_center > 0.5f) {
      if (dist_to_up < dist_to_down) {
        float val = fmin(player->speed, dist_to_up);

        if (physics_can_move_to(
                (Vector2){new_pos.x, new_pos.y + val + PLAYER_HEIGHT_TOLERANCE},
                player->entity.width, player->entity.height))
          new_pos.y += val;

      } else if (dist_to_down < dist_to_up) {
        float val = fmin(player->speed, dist_to_down);

        if (physics_can_move_to(
                (Vector2){new_pos.x, new_pos.y - val + PLAYER_HEIGHT_TOLERANCE},
                player->entity.width, player->entity.height))
          new_pos.y -= val;
      }
    }
  }

  projected.y =
      fmax(MAP_Y_OFFSET, new_pos.y + player->speed * player->input.move.y);

  Vector2 vertical = {player->entity.position.x, projected.y};
  if (physics_can_move_to(
          (Vector2){vertical.x, vertical.y + PLAYER_HEIGHT_TOLERANCE},
          player->entity.width, player->entity.height))
    new_pos.y = vertical.y;
  else if (player->input.move.x == 0) {
    float offset_in_tile = fmod(
        player->entity.position.x + player->entity.width / 2.0f, TILE_SIZE);

    float dist_to_left = offset_in_tile;
    float dist_to_right = TILE_SIZE - offset_in_tile;

    if (dist_to_left < dist_to_right) {
      float val = fmin(player->speed, dist_to_left);

      if (physics_can_move_to(
              (Vector2){new_pos.x - val, new_pos.y + PLAYER_HEIGHT_TOLERANCE},
              player->entity.width, player->entity.height))
        new_pos.x -= val;
    } else if (dist_to_right < dist_to_left) {
      float val = fmin(player->speed, dist_to_right);

      if (physics_can_move_to(
              (Vector2){new_pos.x + val, new_pos.y + PLAYER_HEIGHT_TOLERANCE},
              player->entity.width, player->entity.height))
        new_pos.x += val;
    }
  }

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
    animation_resume(&player->walk_animation);
  } else {
    player->walk_animation.frame_index = 1;
    animation_pause(&player->walk_animation);
  }

  player->entity.position = new_pos;

  animation_update(&player->invencible_animation);
}

void player_draw(Entity *self) {
  Player *player = (Player *)self;

  if (player->death_animation.playing) {
    Texture2D *texture = assets_players_get_death_texture(
        player->id, player->death_animation.frame_index);

    DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
                WHITE);
  } else {
    int frame = player->invencible_animation.frame_index;

    Texture2D *texture = frame == 1 ? assets_players_get_walk_white_texture(
                                          player->entity.direction, frame)
                                    : assets_players_get_walk_texture(
                                          player->id, player->entity.direction,
                                          player->walk_animation.frame_index);

    DrawTexture(*texture, player->entity.position.x, player->entity.position.y,
                WHITE);
  }
}

void player_debug(Entity *self) {
  Player *player = (Player *)self;

  GridPosition pos =
      entity_world_to_grid(&player->entity, PLAYER_HEIGHT_TOLERANCE);
  TileType tile = map_get_tile(game_manager.map, pos);
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
           player->lives, player->walk_animation.frame_index,
           tile == TILE_EMPTY   ? "EMPTY"
           : tile == TILE_WALL  ? "WALL"
           : tile == TILE_BRICK ? "BRICK"
                                : "BOMB");

  Vector2 textSize = MeasureTextEx(GetFontDefault(), strBuffer, 20, 1.0f);

  float x = 15;
  float y = (GAMEPLAY_HEIGHT + MAP_Y_OFFSET) / 2.0f - textSize.y / 2.0f;

  DrawRectangle(x, y, textSize.x + 10, textSize.y + 10,
                (Color){196, 196, 196, 200});

  DrawTextEx(GetFontDefault(), strBuffer, (Vector2){x, y}, 20, 1.0f, BLACK);

  Vector2 grid = map_grid_to_world(pos);

  DrawRectangle(grid.x, grid.y, TILE_SIZE, TILE_SIZE,
                (Color){128, 128, 128, 128});
}

int player_get_all_bombs(Player *player, Entity **out) {
  int count = 0;
  for (int i = 0; i < entities_manager.count && count <= player->bomb_capacity;
       i++) {
    Entity *entity = entities_manager.entries[i];

    Bomb *bomb = (Bomb *)entity;

    if (entity->type == ENTITY_BOMB && bomb->player_id == player->id) {
      if (out != NULL)
        out[count] = entity;
      count++;
    }
  }

  return count;
}

Player *player_at_grid(GridPosition grid) {
  for (int i = 0; i < game_manager.player_count; i++) {
    Player *player = (Player *)game_manager.players[i];

    GridPosition grid2 =
        entity_world_to_grid(&player->entity, PLAYER_HEIGHT_TOLERANCE);

    if (map_is_same_grid(grid, grid2))
      return player;
  }

  return NULL;
}
