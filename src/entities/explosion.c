#include "explosion.h"
#include <stdlib.h>
#include "map.h"
#include "entities_manager.h"

Explosion *explosion_create(int radius,Vector2 position){
    Entity entity;
    entity.type = ENTITY_EXPLOSION;
    entity.layer = LAYER_BOMBS; //Camada de apresentacao
    entity.position = position;
    entity.width = TILE_SIZE;   //tamanho do desenho da animacao
    entity.height = TILE_SIZE;
    entity.update = NULL;
    entity.draw = NULL;
    entity.debug = NULL;

    Explosion *explosion =malloc(sizeof(Explosion));
    explosion->entity=entity;
    explosion->radius=radius;
    explosion->limits_length=0;

    game_manager_on_bomb_exploded(map_world_to_grid(position), radius);

    entities_manager_add((Entity*) explosion);
}