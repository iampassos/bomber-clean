#include "map_renderer.h"
#include "core/animation.h"
#include "core/asset_manager.h"
#include "core/common.h"
#include "core/map.h"
#include "entities/bomb.h"
#include "game/game_manager.h"
#include "map_renderer.h"
#include <raylib.h>
#include <stdio.h>

Animation stage_one_brick_animation;

void map_renderer() {
  map_renderer_background();

  switch (game_manager.map.stage) {
  case MAP_BATTLE_STAGE_1:
    map_renderer_battle_stage_one_tiles();
    break;
  case MAP_STAGE_1:
    if (!animation_is_playing(&stage_one_brick_animation)) {
      animation_init(&stage_one_brick_animation, 4, 0.1f, true);
      animation_play(&stage_one_brick_animation);
    }
    map_renderer_stage_one_tiles();
    break;
  }
}

void map_renderer_background() {
  DrawTexture(*asset_manager_get_map_background_texture(),
              MAP_X_OFFSET - TILE_SIZE, MAP_Y_OFFSET, WHITE);
}

void map_renderer_battle_stage_one_tiles() {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *textures = asset_manager_get_map_tiles_textures();
      Texture2D *text = NULL;

      TileType tile = map_get_tile(&game_manager.map, (GridPosition){j, i});
      TileType upper_tile =
          map_get_tile(&game_manager.map, (GridPosition){j, i - 1});

      switch (tile) {
      case TILE_EMPTY:
        text = upper_tile != TILE_EMPTY ? &textures[4] : NULL;
        break;
      case TILE_BRICK:
        text = &textures[6];
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

void map_renderer_stage_one_tiles() {
  for (int i = 0; i < GRID_HEIGHT; i++) {
    for (int j = 0; j < GRID_WIDTH; j++) {
      Texture2D *textures = asset_manager_get_map_tiles_textures();
      Texture2D *text = NULL;

      TileType tile = map_get_tile(&game_manager.map, (GridPosition){j, i});
      TileType upper_tile =
          map_get_tile(&game_manager.map, (GridPosition){j, i - 1});

      switch (tile) {
      case TILE_EMPTY:
        Bomb *bomb = bomb_at_grid((GridPosition){j, i});

        if (!bomb)
          text = upper_tile != TILE_EMPTY
                     ? upper_tile == TILE_BRICK ? &textures[6] : &textures[5]
                     : NULL;

        break;
      case TILE_BRICK:
        text = upper_tile != TILE_EMPTY
                   ? &textures[8 + stage_one_brick_animation.current_frame]
                   : &textures[12 + stage_one_brick_animation.current_frame];
        break;
      case TILE_WALL:
        break;
      }

      if (text != NULL)
        DrawTexture(*text, MAP_X_OFFSET + j * TILE_SIZE,
                    MAP_Y_OFFSET + i * TILE_SIZE, WHITE);
    }
  }

  animation_update(&stage_one_brick_animation);
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
      snprintf(buff, sizeof(buff), "%d", game_manager.map.grid[i][j]);

      Vector2 textSize = MeasureTextEx(GetFontDefault(), buff, 20, 1.0f);
      DrawTextEx(
          GetFontDefault(), buff,
          (Vector2){center.x - textSize.x / 2.0f, center.y - textSize.y / 2.0f},
          20, 1.0f, WHITE);
    }
  }
}
