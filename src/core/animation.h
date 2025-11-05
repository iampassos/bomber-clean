#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdbool.h>

typedef struct {
  float started_at;
  int total_frames;
  int current_frame;
  float frame_duration;
  float last_frame;
  bool loop;
  bool playing;
  bool ended;

  bool end_and_reverse;
  bool reached_end;
} Animation;

void animation_init(Animation *animation, int total_frames,
                    float frame_duration, bool loop, bool end_and_reverse);
void animation_update(Animation *animation);
void animation_advance(Animation *animation);
void animation_reverse(Animation *animation);

void animation_play(Animation *animation);
void animation_stop(Animation *animation);
void animation_restart(Animation *animation);
void animation_pause(Animation *animation);

float animation_started_at(Animation *animation);
int animation_get_frame(Animation *animation);
bool animation_is_playing(Animation *animation);
bool animation_ended(Animation *animation);

#endif
