#include "animation.h"
#include <raylib.h>

Animation animation_new(int steps, float step_interval, int loop,
                        Texture2D *frames, void (*on_complete)(Animation *),
                        void (*on_update)(Animation *)) {
  Animation animation;
  animation.completed = 0;
  animation.steps = steps;
  animation.current_step = 0;
  animation.last_step_time = GetTime();
  animation.step_interval = step_interval;
  animation.loop = loop;
  animation.frames = frames;
  animation.on_complete = on_complete;
  animation.on_update = on_update;

  return animation;
}

void animation_update(Animation *anim) {
  if (anim->completed && anim->on_complete)
    anim->on_complete(anim);

  if (anim->on_update)
    anim->on_update(anim);

  if (anim->steps <= 0)
    return;

  float current_time = GetTime();

  if (current_time - anim->last_step_time >= anim->step_interval) {
    anim->last_step_time = current_time;
    anim->current_step++;

    if (anim->current_step >= anim->steps) {
      if (anim->loop)
        anim->current_step = 0;
      else
        anim->completed = 1;
    }
  }
}

void animation_update_all() {}
