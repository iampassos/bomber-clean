#ifndef STATE_H
#define STATE_H

#include "bomb.h"
#include "common.h"
#include "map.h"
#include "player.h"

#define MAX_BOMBS 3

typedef enum { NORMAL, DEBUG } ViewMode;

typedef struct State {
  Map map;
  Player players[MAX_PLAYERS];
  int player_count;
  ViewMode view_mode;
  Bombs bombs[MAX_PLAYERS];
} State;

extern State state;

void state_init();

#endif
