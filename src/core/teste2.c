// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define GRID_HEIGHT 13
// #define GRID_WIDTH 15

// typedef enum { EMPTY, BRICK_BREAK, BRICK_UNDERBREAK } CellType;

// // ------------------- LinkedList -------------------
// typedef struct Node {
//     void *data;
//     struct Node *next;
// } Node;

// typedef struct {
//     Node *head;
//     Node *tail;
// } LinkedList;

// LinkedList *list_create() {
//     LinkedList *list = malloc(sizeof(LinkedList));
//     if (!list) return NULL;
//     list->head = list->tail = NULL;
//     return list;
// }

// void list_insert_end(LinkedList *list, void *data) {
//     if (!list) return;
//     Node *newNode = malloc(sizeof(Node));
//     if (!newNode) return;
//     newNode->data = data;
//     newNode->next = NULL;
//     if (!list->head) {
//         list->head = list->tail = newNode;
//     } else {
//         list->tail->next = newNode;
//         list->tail = newNode;
//     }
// }

// void list_free_all(LinkedList *list) {
//     if (!list) return;
//     Node *cur = list->head;
//     while (cur) {
//         Node *del = cur;
//         cur = cur->next;
//         free(del->data);
//         free(del);
//     }
//     free(list);
// }


// void list_remove_node(LinkedList *list, void *target) {
//     if (!list || !list->head) return;
    
//     //removendo o primeiro no
//     if(list->head->data==target){
//       Node *delete=list->head;
//       list->head=list->head->next;

//       if(list->head==NULL) list->tail=NULL;
//       free(delete->data);
//       free(delete);
//     }
//     else{
//       Node *aux=list->head;
      
//       while(aux->next !=NULL){
//         if(aux->next->data==target){ //para um antes
//           Node *delete=aux->next;
//           aux->next=aux->next->next;
//           if(delete == list->tail) list->tail = aux; //atualiza a tail
//           free(delete->data);
//           free(delete);
//           return;
//         }
//         aux=aux->next;
//       }
//     }
// }


// // ------------------- A* structs -------------------
// typedef struct {
//     int row, col;
// } GridPos;

// typedef struct NodeA {
//     GridPos pos;
//     int g, h, f;
//     struct NodeA *parent;
// } NodeA;

// // ------------------- Funções auxiliares -------------------
// int manhattan(GridPos a, GridPos b) {
//     return abs(a.row - b.row) + abs(a.col - b.col);
// }

// int pos_equal(GridPos a, GridPos b) {
//     return a.row == b.row && a.col == b.col;
// }

// NodeA *createNode(GridPos pos, int g, int h, NodeA *parent) {
//     NodeA *n = malloc(sizeof(NodeA));
//     n->pos = pos;
//     n->g = g;
//     n->h = h;
//     n->f = g + h;
//     n->parent = parent;
//     return n;
// }

// // Acha o nó com menor f e remove da lista
// // NodeA *find_lowest_f(LinkedList *list) {
// //     Node *cur = list->head, *prev = NULL, *bestPrev = NULL;
// //     NodeA *bestNode = NULL;
// //     int bestF = 99999;

// //     while (cur) {
// //         NodeA *n = (NodeA *)cur->data;
// //         if (n->f < bestF) {
// //             bestF = n->f;
// //             bestNode = n;
// //             bestPrev = prev;
// //         }
// //         prev = cur;
// //         cur = cur->next;
// //     }

// //     if (!bestNode) return NULL;

// //     // Remove da lista
// //     if (!bestPrev) {
// //         list->head = list->head->next;
// //         if (!list->head) list->tail = NULL;
// //     } else {
// //         bestPrev->next = bestPrev->next->next;
// //         if (!bestPrev->next) list->tail = bestPrev;
// //     }

// //     return bestNode;
// // }

// // Acha o nó com menor f e remove da lista open
// NodeA *find_lowest_f(LinkedList *list) {
//     Node *cur = list->head;
//     NodeA *bestNode = NULL;
//     int bestF = 999999;

//     // 1️⃣ – acha o nó com menor F
//     while (cur) {
//         NodeA *n = (NodeA *)cur->data;
//         if (n->f < bestF) {
//             bestF = n->f;
//             bestNode = n;
//         }
//         cur = cur->next;
//     }

//     if (!bestNode) return NULL;

//     // 2️⃣ – cria uma cópia do NodeA (porque list_remove_node vai dar free)
//     NodeA *copy = malloc(sizeof(NodeA));
//     if (!copy) return NULL;
//     *copy = *bestNode; // cópia rasa — como o parent é ponteiro, isso é suficiente

//     // 3️⃣ – remove o original da lista (libera ele e o nó)
//     list_remove_node(list, bestNode);

//     // 4️⃣ – retorna a cópia
//     return copy;
// }

// //chega se ta na lista
// int in_list(LinkedList *list, GridPos pos) {
//     Node *cur = list->head;
//     while (cur) {
//         NodeA *n = (NodeA *)cur->data;
//         if (pos_equal(n->pos, pos)) return 1;
//         cur = cur->next;
//     }
//     return 0;
// }

// // Reconstrói o caminho
// void reconstruct(NodeA *goal, char visual[GRID_HEIGHT][GRID_WIDTH]) {
//     NodeA *cur = goal;
//     while (cur) {
//         if (visual[cur->pos.row][cur->pos.col] == '.')
//             visual[cur->pos.row][cur->pos.col] = '*';
//         cur = cur->parent;
//     }
// }

// GridPos get_first_move(NodeA *goalNode, GridPos start) {
//     GridPos nextMove = start; // padrão — não move caso não haja caminho

//     if (goalNode == NULL)
//         return nextMove;

//     NodeA *cur = goalNode;
//     NodeA *prev = NULL;

//     // Caminha de trás pra frente até achar o nó cujo pai é o start
//     while (cur->parent != NULL) {
//         prev = cur;
//         cur = cur->parent;
//         if (pos_equal(cur->pos, start)) {
//             nextMove = prev->pos;
//             break;
//         }
//     }

//     return nextMove;
// }

// // ------------------- A* -------------------
// GridPos a_star(CellType grid[GRID_HEIGHT][GRID_WIDTH], GridPos start, GridPos goal, char visual[GRID_HEIGHT][GRID_WIDTH]) {
//     LinkedList *open = list_create();
//     LinkedList *closed = list_create();
//     GridPos nextMove = start;

//     NodeA *startNode = createNode(start, 0, manhattan(start, goal), NULL);
//     list_insert_end(open, startNode);

//     int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // cima, baixo, esquerda, direita
//     NodeA *goalNode = NULL;

//     while (open->head) {
//         NodeA *current = find_lowest_f(open);
//         list_insert_end(closed, current);

//         if (pos_equal(current->pos, goal)) {
//             reconstruct(current, visual); // opcional, debug
//             goalNode = current;
//             break;
//         }

//         for (int i = 0; i < 4; i++) {
//             int nr = current->pos.row + dirs[i][0];
//             int nc = current->pos.col + dirs[i][1];

//             if (nr < 0 || nr >= GRID_HEIGHT || nc < 0 || nc >= GRID_WIDTH) continue;
//             if (grid[nr][nc] != EMPTY) continue;

//             GridPos newPos = {nr, nc};
//             if (in_list(closed, newPos)) continue;
//             if (in_list(open, newPos)) continue;

//             NodeA *neighbor = createNode(newPos, current->g + 1, manhattan(newPos, goal), current);
//             list_insert_end(open, neighbor);
//         }
//     }

//     // 🔹 Aqui chama a função que calcula o primeiro movimento:
//     nextMove = get_first_move(goalNode, start);

//     list_free_all(open);
//     list_free_all(closed);

//     return nextMove;
// }

// // ------------------- Visualização -------------------
// void printGrid(char visual[GRID_HEIGHT][GRID_WIDTH]) {
//     for (int i = 0; i < GRID_HEIGHT; i++) {
//         for (int j = 0; j < GRID_WIDTH; j++)
//             printf("%c ", visual[i][j]);
//         printf("\n");
//     }
//     printf("\n");
// }

// // ------------------- Main -------------------
// int main() {
//     CellType grid[GRID_HEIGHT][GRID_WIDTH];
//     char visual[GRID_HEIGHT][GRID_WIDTH];

//     // Inicializa grid e visual
//     for (int i=0;i<GRID_HEIGHT;i++){
//         for (int j=0;j<GRID_WIDTH;j++){
//             if (i==0 || i==GRID_HEIGHT-1 || j==0 || j==GRID_WIDTH-1){
//                 grid[i][j] = BRICK_UNDERBREAK;
//                 visual[i][j] = '#';
//             } else {
//                 grid[i][j] = EMPTY;
//                 visual[i][j] = '.';
//             }
//         }
//     }

//     // Obstáculos internos
//     grid[2][1] = BRICK_UNDERBREAK; visual[2][1] = '#';
//     grid[2][3] = BRICK_UNDERBREAK; visual[2][3] = '#';
//     grid[2][4] = BRICK_UNDERBREAK; visual[2][4] = '#';
//     grid[3][4] = BRICK_UNDERBREAK; visual[3][4] = '#';
//     grid[4][4] = BRICK_UNDERBREAK; visual[4][4] = '#';
//     grid[5][7] = BRICK_UNDERBREAK; visual[5][7] = '#';
//     grid[6][7] = BRICK_UNDERBREAK; visual[6][7] = '#';
//     grid[8][5] = BRICK_UNDERBREAK; visual[8][5] = '#';
//     grid[8][6] = BRICK_UNDERBREAK; visual[8][6] = '#';
//     grid[9][6] = BRICK_UNDERBREAK; visual[9][6] = '#';
//     grid[3][10] = BRICK_UNDERBREAK; visual[3][10] = '#';
//     grid[4][10] = BRICK_UNDERBREAK; visual[4][10] = '#';
//     grid[5][10] = BRICK_UNDERBREAK; visual[5][10] = '#';
//     grid[6][12] = BRICK_UNDERBREAK; visual[6][12] = '#';
//     grid[7][12] = BRICK_UNDERBREAK; visual[7][12] = '#';
//     grid[9][8] = BRICK_UNDERBREAK; visual[9][8] = '#';
//     grid[10][8] = BRICK_UNDERBREAK; visual[10][8] = '#';

//     GridPos start = {1,1};
//     GridPos goal = {10,13};
//     visual[start.row][start.col] = 'S';
//     visual[goal.row][goal.col] = 'G';

//     printf("Mapa inicial:\n");
//     printGrid(visual);

//     //a_star(grid, start, goal, visual);
//      GridPos nextMove = a_star(grid, start, goal, visual);

//     printf("Caminho encontrado:\n");
//     printGrid(visual);

//     printf("\n Próximo movimento sugerido: (%d, %d)\n", nextMove.row, nextMove.col);

//     return 0;
// }
