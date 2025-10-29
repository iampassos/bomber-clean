#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

typedef struct Animation {
  int completed;
  int steps;
  int current_step;
  float last_step_time;
  float step_interval;
  int loop;
  Texture2D *frames;
  void (*on_complete)(struct Animation *);
  void (*on_update)(struct Animation *);
} Animation;

Animation animation_new(int steps, float step_interval, int loop,
                        Texture2D *frames, void (*on_complete)(Animation *),
                        void (*on_update)(Animation *));
void animation_update(Animation *anim);
void animation_update_all();
#endif
