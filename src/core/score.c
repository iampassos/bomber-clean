#include "score.h"
#include "entities/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap_Score(Score *a, Score *b) {
  Score temp = *a;
  *a = *b;
  *b = temp;
}

void insertion_sort_score_by_time(Score *array, int len) {
  if (array != NULL) {
    for (int i = 1; i < len; i++) {
      int current = i;
      while (current != 0 && array[current].time < array[current - 1].time) {
        swap_Score(&array[current], &array[current - 1]);
        current--;
      }
    }
  }
}

void insert_score(int id, double time) {
  FILE *file;
  file = fopen("Ranking.txt", "a");
  if (!file)
    return;
  fprintf(file, "Jogador %d Tempo: %.3lf\n", id, time * 1000);
  fclose(file);
}
void insert_party_score(int id, double time) {
  FILE *file;
  file = fopen("Party.txt", "a");
  if (!file)
    return;
  fprintf(file, "Jogador %d Tempo: %.3lf\n", id, time * 1000);
  fclose(file);
}

void score_set_player(Player *p1) {
  if (p1 != NULL) {
    insert_score(p1->id, p1->death_life_time);
    insert_party_score(p1->id, p1->death_life_time);
  } else {
    return;
  }
}

char *score_get() {
  FILE *file;
  file = fopen("Ranking.txt", "r");
  if (!file)
    return NULL;
  Score *array = malloc(100 * sizeof(Score));
  if (!array)
    return NULL;
  int cont = 0;
  while (fscanf(file, "Jogador %d Tempo: %lf\n", &array[cont].id,
                &array[cont].time) == 2) {
    cont++;
    if (cont >= 100)
      break;
  }
  fclose(file);
  insertion_sort_score_by_time(array, cont);
  char *tabela = malloc(10000);
  tabela[0] = '\0';
  for (int i = 0; i < cont; i++) {
    char linha[100];
    sprintf(linha, "Jogador %d Tempo: %.3lf\n", array[i].id, array[i].time);
    strcat(tabela, linha);
  }

  free(array);
  return tabela;
}

char *party_get_ranking() {
  FILE *file;
  file = fopen("Party.txt", "r");
  if (!file)
    return NULL;
  Score *array = malloc(100 * sizeof(Score));
  if (!array)
    return NULL;
  int cont = 0;
  while (fscanf(file, "Jogador %d Tempo: %lf\n", &array[cont].id,
                &array[cont].time) == 2) {
    cont++;
    if (cont >= 100)
      break;
  }
  fclose(file);
  insertion_sort_score_by_time(array, cont);
  char *tabela = malloc(10000);
  tabela[0] = '\0';
  for (int i = 0; i < cont; i++) {
    char linha[100];
    sprintf(linha, "Jogador %d Tempo: %.3lf\n", array[i].id, array[i].time);
    strcat(tabela, linha);
  }

  free(array);
  return tabela;
}
