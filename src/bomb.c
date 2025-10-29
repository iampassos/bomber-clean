#include "bomb.h"

void bomb_insert(ArrayBomb *array,GridPosition pos){
    if(array->current_length >= MAX_BOMBS) return;

    Bomb newBomb;
    newBomb.grid_position=pos;
    newBomb.spawn_time=GetTime();
    newBomb.animation_step=0;
    newBomb.last_animation_step=0.0f;
    array->bombs[(array->current_length)++]=newBomb;
}

void bomb_clear_all(ArrayBomb *array){
    array->current_length=0;
}

void bomb_remove_per_idx(ArrayBomb *array, int idx_remove){
    if(idx_remove <0 || idx_remove>=array->current_length) return;

    for(int i= idx_remove; i < array->current_length-1; i++){
        array->bombs[i]=array->bombs[i+1];
    }
    array->current_length--;
}

Bomb *bomb_find_idx(ArrayBomb *arry,int idx){
    if(idx<0 || idx>=arry->current_length) return NULL;
    return &arry->bombs[idx];
}

bool bomb_remove_by_grid_position(ArrayBomb *array, GridPosition pos){
    if(array->current_length==0) return false;

    for(int i=0;i<array->current_length;i++){
        if(array->bombs[i].grid_position.col == pos.col && array->bombs[i].grid_position.row==pos.row) {
            bomb_remove_per_idx(array,i);
            return true;
        }
    }
    return false;
}

Bomb *bomb_find_on_grid_position(ArrayBomb *array, GridPosition pos){
    
    if(array->current_length==0) return NULL;

    for (int i=0; i<array->current_length;i++){
        if(array->bombs[i].grid_position.row == pos.row && array->bombs[i].grid_position.col == pos.col) return &array->bombs[i];
    }

    return NULL;
}

void bombs_increase_time_to_explode(ArrayBomb *array) {
    for (int i = 0; i < array->current_length; i++) {
        array->bombs[i].spawn_time += PLUS_EXPLODE_DELAY;
    }
}



int bomb_find_to_explode(ArrayBomb *array) {
    for (int i = 0; i < array->current_length; i++) {
        if (GetTime() - array->bombs[i].spawn_time >= EXPLODE_DELAY)
            return i;
    }
    return -1;
}

void bombs_update_all(ArrayBomb *array) {

    int idx;
    while (1) {
    idx = bomb_find_to_explode(array);
    
    if (idx == -1) break; //sem bomba para explodir
    bomb_remove(array, idx);
    }

    for (int i = 0; i < array->current_length; i++) {  //Atualiza as animacoes da bomba
        if (GetTime() - array->bombs[i].last_animation_step >= EXPLODE_DELAY / 10.0f) {
            array->bombs[i].animation_step = (array->bombs[i].animation_step + 1) % 3;
            array->bombs[i].last_animation_step = GetTime();
        }
    }
}


//DFS 

void bomb_dfs(GridPosition pos, TileType grid[GRID_HEIGHT][GRID_WIDTH], int visited[GRID_HEIGHT][GRID_WIDTH]){
    if (pos.col < 0 || pos.col >= GRID_WIDTH || pos.row < 0 || pos.row >= GRID_HEIGHT) return;

    if(visited[pos.row][pos.col] == 1|| grid[pos.row][pos.col]!= TILE_EMPTY) return;

    visited[pos.row][pos.col]=1;

    bomb_dfs((GridPosition){pos.col + 1, pos.row}, grid, visited); // direita
    bomb_dfs((GridPosition){pos.col - 1, pos.row}, grid, visited); // esquerda
    bomb_dfs((GridPosition){pos.col, pos.row + 1}, grid, visited); // baixo
    bomb_dfs((GridPosition){pos.col, pos.row - 1}, grid, visited); // cima
  
}

int bomb_get_spawnable_positions(GridPosition *bomb_validedd_position_in_grid, GridPosition player_position, TileType grid[GRID_HEIGHT][GRID_WIDTH]) {
    int visited[GRID_HEIGHT][GRID_WIDTH] = {0};

    bomb_dfs(player_position, grid, visited);

    int count = 0;
    for (int row = 0; row < GRID_HEIGHT; row++) {
        for (int col = 0; col < GRID_WIDTH; col++) {
            if(row == player_position.row && col == player_position.col) continue;
            if (visited[row][col] == 1) bomb_validedd_position_in_grid[count++] = (GridPosition){col, row};
        }
    }
    return count; 
}