#include <raylib.h>
#include <stdlib.h>

typedef struct Bomb {
    Vector2      position;
    double       spawn_time;
    struct Bomb *next;
} Bomb;
