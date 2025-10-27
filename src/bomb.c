#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <map.h>
#include <time.h>

typedef struct Bomb{
    Vector2 posi;
    double spawnTime;

    struct Bomb *next;
    struct Bomb *prev;
}Bomb;

typedef struct Bombs{
    struct Bomb *head;
    struct Bomb *tail;
    int currentLength;
    int totalCreated;
}Bombs;

void create_bombs_list(Bombs *list){
    list->head=NULL;
    list->tail=NULL;
    list->currentLength=0;
    list->totalCreated=0;
}

//insersão no final de uma bomba
void insert_bomb(Bombs *list, Vector2 posi){
    Bomb *newBomb = malloc(sizeof(Bomb));
    if( newBomb==NULL ) return;

    list->totalCreated++;
    list->currentLength++;
    newBomb->posi=posi;
    newBomb->spawnTime=GetTime();
    newBomb->next=NULL;

     //insersão com um elemento
    if(list->head==NULL){
        newBomb->next =newBomb->prev =newBomb;
        list->head=list->tail=newBomb;
    }
    else{
        list->tail->next=newBomb;
        newBomb->prev=list->tail;
        list->tail=newBomb;
        newBomb->next=list->head;
        list->head->prev=newBomb;
    }
}

//remosao no final de bomba
void remove_bomb(Bombs *list){
    if(list==NULL || list->head==NULL) return;
    
    list->currentLength--;
    Bomb *delete=list->tail;

    if(list->head==list->tail) list->head=list->tail=NULL;
    else{
        list->tail=list->tail->prev;
        list->tail->next=list->head;
        list->head->prev=list->tail;
    }
    free(delete);
}

void free_list(Bombs *list){
    if(list!=NULL && list->head!=NULL){
        while(list->head!=NULL) remove_bomb(list);
        list->currentLength=0;
        list->totalCreated=0;
    }
}


bool is_possible_insert_bomb_in_map(Bombs *list,Vector2 spawn_posi,TileType tile){
    if(tile!=TILE_EMPTY) return false;
    if(list!=NULL && list->head!=NULL){
        Bomb *current=list->head;
        do{
            if(spawn_posi.x == current->posi.x && spawn_posi.y==current->posi.y) return false;
            current=current->next;
        }while(current!=list->head);
    }
    return true;
}