#ifndef ENTITIES_MANAGER_H
#define ENTITIES_MANAGER_H

#include "core/map.h"
#include "entity.h"

#define MAX_ENTITIES 256

typedef struct {
  Entity *entries[MAX_ENTITIES];
  int count;
} EntitiesManager;

//Instancia global do gerenciador de entidades
extern EntitiesManager entities_manager;

void entities_manager_init(); //unicializa o gerenciador de entidades
void entities_manager_add(Entity *entity); //Adiciona uma entidade ao jogo se houver espaço
void entities_manager_remove(Entity *entity);
void entities_manager_update_all(); // chama a função de update de todas entidades do jogo
void entities_manager_draw_all();  // chama a função de desenhar todas as entidades do jogo
void entities_manager_draw_all_layer(EntityLayer layer); // desenha a entidade aparti da prioridade das camadas
void entities_manager_debug_all(); 
void entities_manager_clear(); //desaloca todas entidades do jogo
void entities_manager_clear_but_player(); //remove todas entidades exceto o jogador

// retorna todas as entidades que estão em um grid position
int entities_manager_get_all_at_grid(GridPosition grid, Entity **out,
                                     int max_out);
// retorna todas entidades de um tipo especifico
int entities_manager_get_all_from_type(EntityType type, Entity **out,
                                       int max_out);

void entities_manager_debug();
void entities_manager_hitboxes();
void entities_manager_grid();

#endif
