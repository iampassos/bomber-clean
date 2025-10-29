#ifndef STATE_H
#define STATE_H

#include "bomb.h"
#include "common.h"
#include "map.h"
#include "player.h"

typedef enum { NORMAL, DEBUG } ViewMode;

typedef struct State {
  Map map;
  Players players;
  ViewMode view_mode;
  Bombs bombs[MAX_PLAYERS];
} State;

extern State state;

void state_init();

#endif
