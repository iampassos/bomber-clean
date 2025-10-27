#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

typedef struct Bombs{
    struct Bombs *head;
    struct Bombs *tail;
    int lenght;
}Bombs;

typedef struct Bomb{
    Vector2 posi;
    double spawnTime;
}Bomb;

void createBombsList(Bombs *list){
    list->head=NULL;
    list->tail=NULL;
    list->lenght=0;
}