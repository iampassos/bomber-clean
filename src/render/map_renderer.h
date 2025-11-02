#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "core/map.h"

void map_renderer();
void map_renderer_background();
void map_renderer_brick_animation();
void map_renderer_brick_destruction();
void map_renderer_animate_brick_destruction(GridPosition grid);
void map_renderer_battle_stage_one_tiles();
void map_renderer_peace_town_tiles();
void map_renderer_debug();

#endif
