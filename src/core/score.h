#ifndef SCORE_H
#define SCORE_H

#include "entities/player.h"

typedef struct Score {
  int id;
  double time;
} Score;

void score_set_player(Player *p1);
int score_get(Score *out, int max);

#endif
