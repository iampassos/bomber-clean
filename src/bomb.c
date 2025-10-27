#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
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

void createBombsList(Bombs *list){
    list->head=NULL;
    list->tail=NULL;
    list->currentLength=0;
    list->totalCreated=0;
}

//insersão no final de uma bomba
void insertBomb(Bombs *list, Vector2 posi, double spawnTime){
    Bomb *newBomb = malloc(sizeof(Bomb));
    if( newBomb==NULL ) return;

    list->totalCreated++;
    list->currentLength++;
    newBomb->posi=posi;
    newBomb->spawnTime=spawnTime;
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
void removeBomb(Bombs *list){
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

void freeList(Bombs *list){
    if(list!=NULL && list->head!=NULL){
        while(list->head!=NULL) removeBomb(list);
        list->currentLength=0;
        list->totalCreated=0;
    }
}

bool isPossibleInsertBombInMap(){
    return false;
}