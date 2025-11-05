#include "path_finding.h"


//Funcao para calcular a heuristisca ( Distancia do No atual para o alvo )
int manhattan(GridPosition a, GridPosition b){
    return  abs(a.row-b.row) + abs(b.col-b.col);
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



//deletar dps
//deletar dps
//deletar dps
void reconstruct(NodeA *goal, char visual[GRID_HEIGHT][GRID_WIDTH]) {
    NodeA *cur = goal;
    while (cur) {
        if (visual[cur->grid.row][cur->grid.col] == '.')
            visual[cur->grid.row][cur->grid.col] = '*';
        cur = cur->parent;
    }
}
//deletar dps
//deletar dps
//deletar dps


//Funcao A_Star

