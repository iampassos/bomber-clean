#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_WIDTH 15
#define GRID_HEIGHT 13

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_BRICK,
} TileType;

typedef struct {
    int col;
    int row;
} GridPosition;

void bomb_dfs(GridPosition pos, TileType grid[GRID_HEIGHT][GRID_WIDTH], int visited[GRID_HEIGHT][GRID_WIDTH]){
    if (pos.col < 0 || pos.col >= GRID_WIDTH || pos.row < 0 || pos.row >= GRID_HEIGHT) return;
    if(visited[pos.row][pos.col] == 1 || grid[pos.row][pos.col] != TILE_EMPTY) return;

    visited[pos.row][pos.col] = 1;

    bomb_dfs((GridPosition){pos.col + 1, pos.row}, grid, visited); // direita
    bomb_dfs((GridPosition){pos.col - 1, pos.row}, grid, visited); // esquerda
    bomb_dfs((GridPosition){pos.col, pos.row + 1}, grid, visited); // baixo
    bomb_dfs((GridPosition){pos.col, pos.row - 1}, grid, visited); // cima
}

int bomb_get_spawnable_positions(GridPosition *bomb_validedd_position_in_grid, GridPosition player_position, TileType grid[GRID_HEIGHT][GRID_WIDTH]){
    int visited[GRID_HEIGHT][GRID_WIDTH] = {0};

    bomb_dfs(player_position, grid, visited);

    int count = 0;
    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            if(row == player_position.row && col == player_position.col) continue;
            if (visited[row][col] == 1) 
                bomb_validedd_position_in_grid[count++] = (GridPosition){col, row};
        }
    }
    return count;
}

void debug_spawn(TileType grid[GRID_HEIGHT][GRID_WIDTH], GridPosition *spawn_positions, int spawn_count){
    char display[GRID_HEIGHT][GRID_WIDTH];
    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            switch(grid[row][col]){
                case TILE_EMPTY: display[row][col] = '.'; break;
                case TILE_WALL: display[row][col] = '#'; break;
                case TILE_BRICK: display[row][col] = '+'; break;
            }
        }
    }

    // Marca as posições válidas com '*'
    for (int i = 0; i < spawn_count; i++){
        GridPosition p = spawn_positions[i];
        display[p.row][p.col] = '*';
    }

    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            printf("%c ", display[row][col]);
        }
        printf("\n");
    }
}

int main(){
    TileType grid[GRID_HEIGHT][GRID_WIDTH];
    srand(time(NULL));

    // Inicializa o grid aleatório
    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            int r = rand() % 100;
            if(r < 60)
                grid[row][col] = TILE_EMPTY;   // 60% vazio
            else if(r < 80)
                grid[row][col] = TILE_WALL;    // 20% parede
            else
                grid[row][col] = TILE_BRICK;   // 20% tijolo
        }
    }

    for (int row = 0; row < GRID_HEIGHT; row++){
        for (int col = 0; col < GRID_WIDTH; col++){
            if(col==0 || row ==0 || row==12 || col ==14) grid[row][col]=TILE_WALL;
        }
    }

    //grid[0][1]=TILE_WALL;
    //grid[1][0]=TILE_WALL;

    // . vazio
    // # muro
    // + muro quebradico
    // *posicao possiveis

    GridPosition player_pos = {1,1};
    // Garante que o player não começa em parede/tijolo
    grid[player_pos.row][player_pos.col] = TILE_EMPTY;

    GridPosition spawn_positions[GRID_WIDTH * GRID_HEIGHT];
    int count = bomb_get_spawnable_positions(spawn_positions, player_pos, grid);

    printf("Número de posições válidas: %d\n", count);
    debug_spawn(grid, spawn_positions, count);

    // Escolher posição aleatória
    if(count > 0){
        int idx = rand() % count;
        GridPosition chosen = spawn_positions[idx];
        printf("Posição aleatória escolhida: (%d, %d)\n", chosen.col, chosen.row);
    }

    return 0;
}
