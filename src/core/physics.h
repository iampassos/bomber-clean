#ifndef PHYSICS_H
#define PHYSICS_H

#include "entities/entity.h"
#include <raylib.h>

bool physics_can_move_to(Vector2 projected, float width, float height);
bool physics_entity_collision(Entity *entity1, Entity *entity2);

#endif
