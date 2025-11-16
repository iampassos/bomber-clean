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
    if (array != NULL) { // verificação se o ponteiro está apontando pra algo
        for (int i = 1; i < len; i++) {
            int current = i;
            while (current != 0 && array[current].time > array[current - 1].time) {
                swap_Score(&array[current], &array[current - 1]);
                current--; // Finalização do InsertionSort
            }
        }
    }
}

void insert_score(int id, double time) {
    FILE *file; // Inicialização do ponteiro para criação do arquivo.
    file = fopen("Ranking.txt", "a"); // criação ou inserção nova de linha no arquivo de Ranking Geral
    if (!file) // verificação se o ponteiro está apontando para o fopen ao inves de nada
        return;

    fprintf(file, "Jogador %d Tempo: %.3lf\n", id, time * 1000); // escritura no arquivo o id do jogador e o tempo em milesimos
    fclose(file); // salvamento do arquivo
}

void insert_party_score(int id, double time) {
    FILE *file; // criação ponteiro de file;
    file = fopen("Party.txt", "a");
    if (!file)
        return;

    fprintf(file, "Jogador %d Tempo: %.3lf\n", id, time * 1000); // escritura tempo em milesimos;
    fclose(file); // salvamento arquivo
}

void score_set_player(Player *p1) { // função para setar o player
    if (p1 != NULL) {
        insert_score(p1->id, p1->death_life_time); // seta o player no score geral
        insert_party_score(p1->id, p1->death_life_time); // seta o player no score da party
    } else {
        return; // retornar caso nenhuma das condições tenham sido realizadas
    }
}

int score_get(Score *out, int max) { // função que lê o Ranking.txt e preenche o vetor 'out'
    FILE *file; // cria o ponteiro para o arquivo
    file = fopen("Ranking.txt", "r"); // abre o arquivo em modo leitura
    if (!file) return -1; // se não conseguiu abrir, retorna erro
    if (!out) return -1; // se o vetor for inválido, retorna erro
    int cont = 0; // contador de quantos registros foram lidos
    while (cont < max && fscanf(file, "Jogador %d Tempo: %lf\n", &out[cont].id, &out[cont].time) == 2) { // lê id e tempo enquanto houver espaço
        cont++; // incrementa o contador quando lê um jogador
    }
    fclose(file); // fecha o arquivo depois da leitura
    insertion_sort_score_by_time(out, cont); // ordena os tempos em ordem crescente
    return cont; // retorna quantos jogadores foram lidos
}


char *party_get_ranking() {
    FILE *file = fopen("Party.txt", "r"); // leitura do arquivo de party
    if (!file)
        return NULL;

    Score *array = malloc(100 * sizeof(Score)); // alocação de memoria para 100 players
    if (!array)
        return NULL;

    int cont = 0; // Inicialização do contador
    while (fscanf(file, "Jogador %d Tempo: %lf\n", &array[cont].id, &array[cont].time) == 2) {
        cont++;
        if (cont >= 100) // se o cont chegar a 100 ou ser maior ele da um break
            break;
    }

    fclose(file);
    insertion_sort_score_by_time(array, cont); // faz a ordenação

    char *tabela = malloc(10000); // faz o malloc dos caracteres
    tabela[0] = '\0'; // inicia tabela com o /0

    for (int i = 0; i < cont; i++) {
        char linha[100];
        sprintf(linha, "Jogador %d Tempo: %.3lf\n", array[i].id, array[i].time); // sprinta a string
        strcat(tabela, linha); // concatena as strings
    }

    free(array); // limpa o array
    return tabela; // retorna tabela
}

