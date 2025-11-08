#ifndef STATE_H
#define STATE_H

typedef struct {
  void (*update)();
  void (*render)();
} State;

#endif
