#include "animation.h"
#include <raylib.h>
#include <stdio.h>

void animation_init(Animation *animation, int total_frames,
                    float frame_duration, bool loop, bool end_and_reverse) {
  animation->total_frames = total_frames;
  animation->current_frame = 0;
  animation->frame_duration = frame_duration;
  animation->last_frame = GetTime();
  animation->loop = loop;
  animation->playing = false;
  animation->ended = false;
  animation->end_and_reverse = end_and_reverse;
  animation->reached_end = false;
}

void animation_update(Animation *animation) {
  if (!animation || !animation->playing || animation->ended)
    return;

  float now = GetTime();
  if (now - animation->last_frame < animation->frame_duration)
    return;

  animation->last_frame = now;

  if (animation->reached_end && animation->end_and_reverse)
    animation_reverse(animation);
  else
    animation_advance(animation);
}

void animation_advance(Animation *animation) {
  if (!animation)
    return;

  if (animation->current_frame + 1 >= animation->total_frames) {
    animation->reached_end = true;

    if (animation->end_and_reverse) {
      animation->current_frame--;
    } else if (animation->loop) {
      animation_restart(animation);
    } else {
      animation_stop(animation);
      animation->ended = true;
    }
  } else {
    animation->current_frame++;
  }
}

void animation_reverse(Animation *animation) {
  if (!animation)
    return;

  if (animation->current_frame <= 0) {
    if (animation->loop) {
      animation->reached_end = false;
      animation->current_frame++;
    } else {
      animation_stop(animation);
      animation->ended = true;
    }
  } else {
    animation->current_frame--;
  }
}

void animation_play(Animation *animation) {
  animation->playing = true;
  animation->ended = false;
}

void animation_stop(Animation *animation) {
  animation->playing = false;
  animation->ended = false;
  animation->current_frame = 0;
  animation->last_frame = GetTime();
}

void animation_restart(Animation *animation) {
  animation_play(animation);
  animation->current_frame = 0;
  animation->last_frame = GetTime();
}

void animation_pause(Animation *animation) { animation->playing = false; }

int animation_get_frame(Animation *animation) {
  return animation->current_frame;
}

bool animation_is_playing(Animation *animation) { return animation->playing; }

bool animation_ended(Animation *animation) { return animation->ended; }
