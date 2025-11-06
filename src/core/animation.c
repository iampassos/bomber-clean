#include "animation.h"
#include <raylib.h>
#include <string.h>

void animation_init(Animation *anm, int *frames, int frame_count,
                    float frame_time, bool loops, bool play) {
  anm->frame_count = frame_count;
  anm->frame_index = 0;
  memcpy(anm->frames, frames, frame_count * sizeof(int));
  anm->frame_time = frame_time;
  anm->loops = loops;
  anm->playing = play;
  anm->started_at = GetTime();
}

void animation_play(Animation *anm) {
  anm->playing = true;
  anm->started_at = GetTime();
}

void animation_pause(Animation *anm) { anm->playing = false; }

void animation_resume(Animation *anm) { anm->playing = true; }

int animation_total_ticks(Animation *anm) {
  return animation_elapsed(anm) / anm->frame_time;
}

void animation_reset(Animation *anm) {
  anm->playing = false;
  anm->started_at = GetTime();
  anm->frame_index = 0;
}

void animation_finish(Animation *anm) {
  animation_reset(anm);
  anm->frame_index = anm->frame_count - 1;
  anm->loops = false;
}

void animation_update(Animation *anm) {
  if (!anm->playing)
    return;

  float elapsed = animation_elapsed(anm);
  int index = elapsed / anm->frame_time;

  if (anm->loops)
    index %= anm->frame_count;
  else if (index >= anm->frame_count) {
    index = anm->frame_count - 1;
    anm->playing = false;
  }

  anm->frame_index = index;
}

int animation_get_frame(Animation *anm) {
  return anm->frames[anm->frame_index];
}

float animation_elapsed(Animation *anm) { return GetTime() - anm->started_at; };

bool animation_is_finished(Animation *anm) {
  return !anm->playing && anm->frame_index == anm->frame_count - 1 &&
         !anm->loops;
}
