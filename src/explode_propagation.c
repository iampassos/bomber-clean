#include "explode_propagation.h"

Bombpropagation bomb_check_explode_propagation(Bombs *array,int idx){
    Bombpropagation explode_propagation = {0};
    //state.map.grid[][]
    int bomb_radius=array->bombs[idx].explosion_radius;
    GridPosition bomb_posi=array->bombs[idx].grid_position;

    //Para baixo
    for(int r=1 ; r <= bomb_radius;r++){
        int row=bomb_posi.row+r;
        if(state.map.grid[row][bomb_posi.col] == TILE_EMPTY){
            explode_propagation.grid_explode_animetion[explode_propagation.lenght_grid_explode_animetion++] = (GridPosition) { row , bomb_posi.col};
        }
        else if(state.map.grid[row][bomb_posi.col] == TILE_BRICK){
            explode_propagation.grid_destroyer[explode_propagation.lenght_grid_destroyer++] = (GridPosition) { row , bomb_posi.col};
            break;
        }
        else break;
    }

    //Para cima

    for(int r=1; r<= bomb_radius;r++){
        int row = bomb_posi.row-r;
        int cow = bomb_posi.col;
        TileType tile = state.map.grid[row][cow];

        if(tile ==TILE_EMPTY){
            explode_propagation.grid_explode_animetion[explode_propagation.lenght_grid_explode_animetion++] = (GridPosition) {row,cow};
        }
        else if(tile== TILE_BRICK) {
            explode_propagation.grid_destroyer[explode_propagation.lenght_grid_destroyer++] = (GridPosition) {row,cow};
            break;
        }
        else break;        
    }

    //Para direita

    for(int r = 1; r<bomb_radius ;r++){
        int row=bomb_posi.row;
        int cow = bomb_posi.col  + r;

        TileType tile = state.map.grid[row][cow];

        if(tile ==TILE_EMPTY){
            explode_propagation.grid_explode_animetion[explode_propagation.lenght_grid_explode_animetion++] = (GridPosition) {row,cow};
        }
        else if(tile== TILE_BRICK) {
            explode_propagation.grid_destroyer[explode_propagation.lenght_grid_destroyer++] = (GridPosition) {row,cow};
            break;
        }
        else break;            
    }

    //Para esquerda

    for(int r = 1; r<bomb_radius ;r++){
        int row=bomb_posi.row;
        int cow = bomb_posi.col  - r;

        TileType tile = state.map.grid[row][cow];

        if(tile ==TILE_EMPTY){
            explode_propagation.grid_explode_animetion[explode_propagation.lenght_grid_explode_animetion++] = (GridPosition) {row,cow};
        }
        else if(tile== TILE_BRICK) {
            explode_propagation.grid_destroyer[explode_propagation.lenght_grid_destroyer++] = (GridPosition) {row,cow};
            break;
        }
        else break;
    }

    return explode_propagation;
}