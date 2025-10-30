#include "animation.h"
#include <raylib.h>

void animation_init(Animation *animation, int total_frames,
                    float frame_duration, bool loop) {
  animation->total_frames = total_frames;
  animation->current_frame = 0;
  animation->frame_duration = frame_duration;
  animation->last_frame = GetTime();
  animation->loop = loop;
  animation->playing = false;
}

void animation_update(Animation *animation) {
  if (!animation->playing)
    return;

  float now = GetTime();

  if (now - animation->last_frame >= animation->frame_duration) {
    animation->last_frame = now;
    animation->current_frame++;

    if (animation->current_frame >= animation->total_frames) {
      if (animation->loop)
        animation_restart(animation);
      else
        animation_stop(animation);
    }
  }
}

void animation_play(Animation *animation) { animation->playing = true; }

void animation_stop(Animation *animation) {
  animation->playing = false;
  animation->current_frame = 0;
  animation->last_frame = GetTime();
}

void animation_restart(Animation *animation) {
  animation->current_frame = 0;
  animation->last_frame = GetTime();
  animation->playing = 1;
}

void animation_pause(Animation *animation) { animation->playing = 0; }

int animation_get_frame(Animation *animation) {
  return animation->current_frame;
}

bool animation_is_playing(Animation *animation) { return animation->playing; }
