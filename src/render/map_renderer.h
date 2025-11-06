#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "core/map.h"

void map_renderer();
void map_renderer_background();
void map_renderer_brick_destruction();
void map_renderer_animate_brick_destruction(GridPosition grid);

void map_renderer_normal_zone_tiles();
void map_renderer_jump_zone_tiles();
void map_renderer_duel_zone_tiles();
void map_renderer_light_zone_tiles();
void map_renderer_speed_zone_tiles();
void map_renderer_belt_zone_tiles();
void map_renderer_western_zone_tiles();
void map_renderer_bomb_zone_tiles();

void map_renderer_debug();

#endif
