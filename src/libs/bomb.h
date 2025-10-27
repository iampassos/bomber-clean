#include <stdlib.h>
#include <raylib.h>

typedef struct Bomb{
    int id;
    Vector2 posi;
    double spanwTime;
    struct Bomb *next;
}Bomb;