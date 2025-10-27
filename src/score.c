#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCORE 200

void creater_txt(char *name, int points, double time) {
  FILE *file = fopen("../../resources/score.txt", "a");

  if (file == NULL)
    return;

  fprintf(file, "%.2f|%d|%s\n", time, points, name);

  fclose(file);
}

void array_score(Score *array) {
  FILE *file = fopen("../../resources/score.txt", "r");

  if (file == NULL) {
    for (int k = 0; k < MAX_SCORE; k++) {
      array[k].name[0] = '\0';
      array[k].points = 0;
      array[k].time = 0.0;
    }
    return;
  }
  int i = 0;
  while (i < MAX_SCORE) {
    double time;
    int points;
    char name[100];

    int ok = fscanf(file, " %lf|%d|%99[^\n]", &time, &points, name);
    if (ok != 3) {
      if (feof(file))
        break;
      int c;
      while ((c = fgetc(file)) != '\n' && c != EOF) {
      }
      continue;
    }

    size_t len = strlen(name);
    if (len && name[len - 1] == '\r')
      name[--len] = '\0';

    array[i].time = time;
    array[i].points = points;

    strncpy(array[i].name, name, sizeof array[i].name);
    array[i].name[sizeof array[i].name - 1] = '\0';
    i++;
  }
  fclose(file);
  for (; i < MAX_SCORE; i++) {
    array[i].name[0] = '\0';
    array[i].points = 0;
    array[i].time = 0.0;
  }
}

void swap_Score(Score *a, Score *b) {
  Score temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort_score_by_time(Score *array, int len) {
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

void print_scores(const Score *v) {
  for (int i = 0; i < MAX_SCORE && v[i].name[0] != '\0'; i++) {
    printf("%2d) time=%.2f  points=%d  name=%s\n", i + 1, v[i].time,
           v[i].points, v[i].name);
  }
}
