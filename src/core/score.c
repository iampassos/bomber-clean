#include "score.h"




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