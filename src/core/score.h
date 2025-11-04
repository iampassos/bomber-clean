#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include "entities/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Score {
  int id;
  double time;
} Score;


void score_get_player(Player *p1);

#endif 
