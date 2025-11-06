#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdbool.h>

#define MAX_FRAMES 16

typedef struct {
  float started_at;
  float frame_time;
  int frames[MAX_FRAMES];
  int frame_count;
  int frame_index;
  bool loops;
  bool playing;
} Animation;

void animation_init(Animation *animation, int *frames, int frame_count,
                    float frame_time, bool loops, bool play);

void animation_update(Animation *animation);
void animation_play(Animation *anm);
void animation_reset(Animation *anm);
void animation_finish(Animation *anm);
void animation_pause(Animation *anm);
void animation_resume(Animation *anm);

int animation_total_ticks(Animation *anm);
int animation_get_frame(Animation *animation);
float animation_elapsed(Animation *animation);

bool animation_is_finished(Animation *animation);

#endif
