#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdbool.h>

typedef struct {
  int total_frames;
  int current_frame;
  float frame_duration;
  float last_frame;
  bool loop;
  bool playing;
} Animation;

void animation_init(Animation *animation, int total_frames,
                    float frame_duration, bool loop);

void animation_play(Animation *animation);
void animation_stop(Animation *animation);
void animation_restart(Animation *animation);
void animation_pause(Animation *animation);

#endif
