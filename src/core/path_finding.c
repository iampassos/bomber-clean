#include "path_finding.h"


//Funcao para calcular a heuristisca ( Distancia do No atual para o alvo )
int manhattan(GridPosition a, GridPosition b){
    return  abs(a.row-b.row) + abs(a.col-b.col);
}

bool is_grid_equal(GridPosition a, GridPosition b){
    return a.row==b.row && a.col==b.col;
}

bool is_in_list(LinkedList *list,GridPosition grid2){
    Node *aux = list->head;
    while(aux!=NULL){
        NodeA *cur =(NodeA *)aux->data;
        if(is_grid_equal(cur->grid,grid2)) return true;
        aux=aux->next;
    }
    return false;
}

NodeA *createNodeA(GridPosition grid,int g,int h,NodeA *parent){
    NodeA *new = malloc(sizeof(NodeA));
    new->grid=grid;
    new->g=g;
    new->h=h;
    new->f=g+h;
    new->parent=parent;
    return new;
}

NodeA *find_low_f(LinkedList *list){
    Node *head = list->head;
    NodeA *bestNode=NULL;

    int bestF = 9999999; //Suponho um valor mt alto

    while(head!=NULL){
        NodeA *aux = (NodeA *)head->data; //cast pra virar um NodeA
        if(aux->f < bestF){
            bestF = aux->f; //Atualiza pro menor novo valor 
            bestNode = aux; //Tipo NodeA
        }
        head = head->next;
    }
    //Nao encontrou o menor vlaor
    if(bestNode==NULL) return NULL;

    NodeA *copy = malloc(sizeof(NodeA));
    if(copy==NULL) return NULL;

    *copy=*bestNode;

    list_remove_node(list,bestNode);

    return copy;
}


GridPosition get_first_move(NodeA *goalNode, GridPosition star){
    if(goalNode==NULL) return star; //n ha caminho

    NodeA *aux =goalNode;

    while(aux->parent!=NULL){
        if(is_grid_equal(aux->parent->grid,star)) return aux->grid; // chega o proximo
        aux=aux->parent;
    }

    return star; // caso n tenha achado algo valido
}


//deletar dps
//deletar dps
//deletar dps
// void reconstruct(NodeA *goal, char visual[GRID_HEIGHT][GRID_WIDTH]) {
//     NodeA *cur = goal;
//     while (cur) {
//         if (visual[cur->grid.row][cur->grid.col] == '.')
//             visual[cur->grid.row][cur->grid.col] = '*';
//         cur = cur->parent;
//     }
// }
//deletar dps
//deletar dps
//deletar dps


//Funcao A_Star

GridPosition path_finding(TileType grid[GRID_HEIGHT][GRID_WIDTH], GridPosition star, GridPosition goal,char visual[GRID_HEIGHT][GRID_WIDTH]){
    LinkedList *open=list_create();
    LinkedList *closed=list_create();

    GridPosition nextMove = star;//se n achar suponho que ele fica parado

    NodeA *starNode = createNodeA(star,0,manhattan(star,goal),NULL); //g ini 0, vizinho null
    list_insert_end(open,starNode);

    //cima, baixo, esquerda, direita
    int d_row[4] = {-1, 1, 0, 0};
    int d_col[4] = {0, 0, -1, 1};
    NodeA *goalNode = NULL;

    while(open->head!=NULL){ //tenho nos abertos para processar
        NodeA *current =find_low_f(open);

        list_insert_end(closed, current);

        if(is_grid_equal(current->grid,goal)){
            //reconstruct(current,visual); //deleta dps deub ***********************
            goalNode=current;
            break;
        }

        for(int i=0;i< 4;i++){
            int new_row = current->grid.row + d_row[i];
            int new_col = current->grid.col + d_col[i];
            
            if(grid[new_row][new_col] != TILE_EMPTY) continue;

            GridPosition new_grid_posi = {new_row,new_col};
            if(is_in_list(open,new_grid_posi)) continue;
            if(is_in_list(closed,new_grid_posi)) continue;

            NodeA *neighbor = createNodeA(new_grid_posi,current->g+1,manhattan(new_grid_posi,goal),current);
            list_insert_end(open,neighbor);
            
        }


    }

    nextMove = get_first_move(goalNode, star);

    list_free_all(open);
    list_free_all(closed);

    return nextMove;
}
