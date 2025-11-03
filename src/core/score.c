// #include "score.h"
// #include "entities/player.h"
// #include <stdio.h>

// void score_get_player(Player *p1){
//     if(p1 != NULL){
//         insert_score(p1->id, p1->time);
//     } else {
//         return;
//     }
// }

// void insert_score(int id, double time){
//     FILE *file;
//     file = fopen("Ranking.txt", "a");
//     if (!file) return;
//     fprintf(file, "Jogador %d Tempo: %lf\n", id, time);
//     fclose(file);
// }

// char *score_get(){
//     FILE *file;
//     file = fopen("Ranking.txt", "r");
//     if (!file) return;
//     Player *array = malloc(sizeof(score));
//     int i = 0;
//     while (fscanf(file, "Jogador %d tempo%lf\n") != EOF)
//     {
//         fprintf("Jogador %d Tempo: %lf", array[i].id, array[i].time);
//         i++;
//     }
//     fclose(file);
//     bubble_sort_score_by_time(scores,count);
    
// }

// void swap_Score(Score *a, Score *b){
//     Score temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void bubble_sort_score_by_time(Score *array, int len){
//     if(array != NULL){
//         for(int i = 1; i < len; i++){
//             int current = i;
//             while(current != 0 && array[current].time < array[current - 1].time){
//                 swap_Score(&array[current], &array[current - 1]);
//                 current--;
//             }
//         }
//     }
// }
