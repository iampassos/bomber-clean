#include "map_renderer.h"
#include "core/animation.h"
#include "core/assets/assets_maps.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/bomb.h"
#include "game/game_manager.h"
#include "map_renderer.h"
#include <raylib.h>
#include <stdio.h>

GridPosition brick_destruction_position[113] = {0};
Animation brick_destruction_animation[113] = {0};
int brick_destruction_length = 0;

void map_renderer() {
  map_renderer_background();

  switch (game_manager.map->stage) {
  case MAP_BATTLE_STAGE_1:
    map_renderer_battle_stage_one_tiles();
    break;
  case MAP_PEACE_TOWN:
    map_renderer_peace_town_tiles();
    break;
  case MAP_JUMP_ZONE:
    map_renderer_jump_zone_tiles();
    break;
  }

  map_renderer_brick_destruction();
}

void map_renderer_background() {
  DrawTexture(*assets_maps_get_background_texture(), MAP_X_OFFSET - TILE_SIZE,
              MAP_Y_OFFSET, WHITE);
}

void map_renderer_brick_destruction() {
  for (int i = 0; i < brick_destruction_length;) {
    Animation *anim = &brick_destruction_animation[i];

    if (anim->playing) {
      Vector2 pos = map_grid_to_world(brick_destruction_position[i]);

      DrawTexture(*assets_maps_get_brick_destruction_texture(anim->frame_index),
                  pos.x, pos.y, WHITE);

      animation_update(anim);
      i++;
    } else {
      brick_destruction_length--;

      brick_destruction_animation[i] =
          brick_destruction_animation[brick_destruction_length];
      brick_destruction_position[i] =
          brick_destruction_position[brick_destruction_length];
    }
  }
}

void map_renderer_animate_brick_destruction(GridPosition grid) {
  animation_init(&brick_destruction_animation[brick_destruction_length],
                 (int[]){0, 1, 2, 3, 4, 5, 6}, 6, 0.125f, false, true);
  brick_destruction_position[brick_destruction_length++] = grid;
}

void map_renderer_battle_stage_one_tiles() {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *textures = assets_maps_get_tiles_textures();
      Texture2D *text = NULL;

      TileType tile = map_get_tile(game_manager.map, (GridPosition){j, i});
      TileType upper_tile =
          map_get_tile(game_manager.map, (GridPosition){j, i - 1});

      switch (tile) {
      case TILE_EMPTY:
        text = upper_tile != TILE_EMPTY ? &textures[0] : NULL;
        break;
      case TILE_BRICK:
        text = &textures[1];
        break;
      case TILE_WALL:
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }
}

void map_renderer_jump_zone_tiles() {
  static int turn = -1;
  static Animation upward = {0};
  static Animation downward = {0};

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *textures = assets_maps_get_tiles_textures();
      Texture2D *text = NULL;

      TileType tile = map_get_tile(game_manager.map, (GridPosition){j, i});
      TileType upper_tile =
          map_get_tile(game_manager.map, (GridPosition){j, i - 1});

      switch (tile) {
      case TILE_EMPTY:
        break;
      case TILE_BRICK:
        // int frame = animation_get_frame(turn == 1 ? &downward : &upward);
        // text = turn == 1 ? &textures[1 + frame] : &textures[4 + frame];
        break;
      case TILE_WALL:
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }
}

void map_renderer_peace_town_tiles() {
  static Animation brick_animation = {0};

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *textures = assets_maps_get_tiles_textures();
      Texture2D *text = NULL;

      TileType tile = map_get_tile(game_manager.map, (GridPosition){j, i});
      TileType upper_tile =
          map_get_tile(game_manager.map, (GridPosition){j, i - 1});

      switch (tile) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_at_grid((GridPosition){j, i});

        if (!bomb)
          text = upper_tile != TILE_EMPTY
                     ? upper_tile == TILE_BRICK ? &textures[1] : &textures[0]
                     : NULL;

        break;
      case TILE_BRICK:
        text = upper_tile != TILE_EMPTY
                   ? &textures[3 + brick_animation.frame_index]
                   : &textures[7 + brick_animation.frame_index];
        break;
      case TILE_WALL:
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }

  if (!brick_animation.playing) {
    animation_init(&brick_animation, (int[]){0, 0, 0, 0}, 4, 0.1f, true, true);
  } else {
    animation_update(&brick_animation);
  }
}

void map_renderer_debug() {
  for (int i = 0; i <= GRID_WIDTH; i++)
    DrawLine(MAP_X_OFFSET + i * TILE_SIZE, MAP_Y_OFFSET,
             MAP_X_OFFSET + i * TILE_SIZE,
             MAP_Y_OFFSET + GRID_HEIGHT * TILE_SIZE, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++)
    DrawLine(MAP_X_OFFSET, MAP_Y_OFFSET + i * TILE_SIZE,
             MAP_X_OFFSET + TILE_SIZE * GRID_WIDTH,
             MAP_Y_OFFSET + i * TILE_SIZE, WHITE);

  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Vector2 center = map_grid_to_world_center((GridPosition){j, i});
      char buff[3];
      snprintf(buff, sizeof(buff), "%d", game_manager.map->grid[i][j]);

      Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
      DrawTextEx(
          GetFontDefault(), buff,
          (Vector2){center.x - textSize.x / 2.0f, center.y - textSize.y / 2.0f},
          20, 1.0f, WHITE);
    }
  }
}
