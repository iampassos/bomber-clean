#include "score.h"
#include "player.h"

void score_get_player(Player *p1,Player *p2,Player *p3,Player *p4){
    if(p1!=NULL){
        //insert_score(p1->id,p1->death_time);
    }
}

void insert_score(int id,double time){
    //inserie no txt
}

char *score_get(){
    
}

void swap_Score(Score *a,Score *b){
    Score temp=*a;
    *a=*b;
    *b=temp;
}

void bubble_sort_score_by_time(Score *array, int len){
    if(array !=NULL){
        for(int i=1;i<len;i++){
            int current=i;
            while(current!=0 && array[current].time < array[current-1].time ){
                swap_Score(&array[current],&array[current-1]);
                current--;
            }
        }
    }
}