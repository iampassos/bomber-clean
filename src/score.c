#include <stdio.h>
#include <string.h>

typedef struct Score {
  char name[100];
  int poits;
  double time;
} Score;

void creater_txt(char *name, int points, double time) {
  FILE *file = fopen("score.txt", "a");

  if (file == NULL)
    return;

  fprintf(file, "%.2f |%d | %s\n", time, points, name);

  fclose(file);
}

void *array_score(Score *array) {
  FILE *file = fopen("score.txt", "r");

  if (file == NULL)
    return NULL;
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
