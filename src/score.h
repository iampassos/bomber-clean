#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME 100
#define MAX_SCORE 200

typedef struct Score {
  char name[100];
  int points;
  double time;
} Score;


void score_creater_txt(char *name, int points, double time);       // Cria (ou adiciona a) um arquivo de texto com o nome, pontos e tempo do jogador
void score_read_from_file(Score *array);                             // Lê o arquivo de pontuações e armazena os dados no array fornecido
void score_insert_sort_by_time(Score *array, int len);    //Ordena o array de Score pelo tempo (menor tempo primeiro)
void scores_prints(const Score *v);                        //Imprime os scores armazenados no array


#endif
