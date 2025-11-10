#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

// ============================================================================
// 🗺️ DIMENSÕES DO JOGO
// ============================================================================

#define GAMEPLAY_WIDTH 1024
#define GAMEPLAY_HEIGHT 896

#define TILE_SIZE 64.0f          // Tamanho de cada tile em pixels
#define GRID_WIDTH 15            // Largura da grade em tiles
#define GRID_HEIGHT 13           // Altura da grade em tiles
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

// Offsets para centralizar o mapa na tela
#define MAP_X_OFFSET (GAMEPLAY_WIDTH / 2.0f - TILE_SIZE * GRID_WIDTH / 2.0f)
#define MAP_Y_OFFSET (GAMEPLAY_HEIGHT - GRID_HEIGHT * TILE_SIZE + TILE_SIZE / 2.0f)

// ============================================================================
// 👤 CONFIGURAÇÕES DE JOGADOR
// ============================================================================

#define MAX_PLAYERS 4            // Quantidade máxima de jogadores
#define MAX_PLAYER_LIVES 5       // Máximo de vidas que um jogador pode ter
#define MAX_PLAYER_SPEED 5.0f * 60.0f   // Velocidade máxima do jogador (pixels/segundo)
#define MAX_PLAYER_BOMBS 5       // Máximo de bombas simultâneas

#define PLAYER_INVENCIBILITY_TIME 7.5f  // Tempo de invencibilidade após morrer
#define PLAYER_DEFAULT_LIVES 3          // Vidas iniciais
#define PLAYER_DEFAULT_SPEED 3.0f * 60.0f  // Velocidade padrão

// ============================================================================
// 💣 CONFIGURAÇÕES DE BOMBAS E EXPLOSÕES
// ============================================================================

#define DEFAULT_BOMB_RADIUS 1
#define DEFAULT_EXPLOSION_LIFETIME 0.6f
#define DEFAULT_BOMBS 1
#define MAX_BOMB_RADIUS 10

// ============================================================================
// 🧱 MAPA E AMBIENTE
// ============================================================================

#define MAP_CHANGE_INTERVAL 45.0f              // Intervalo entre mudanças de mapa
#define PROBABILITY_SPAWN_TILE_BRICK_ON_MAP 30 // Probabilidade (%) de tijolos aparecerem

// ============================================================================
// ⚙️ PROBABILIDADES DE ELEMENTOS
// ============================================================================

#define BOMB_PROBABILITY 50.0f    // Probabilidade de spawn de bombas
#define ENEMY_PROBABILITY 50.0f   // Probabilidade de spawn de inimigos

#define POWER_UP_PROBABILITY 25   // Probabilidade de spawn de power-up
#define POWER_UP_SPEED_INCREASE (MAX_PLAYER_SPEED * 0.05) // Incremento de velocidade
#define POWER_UP_MAP_LIMIT 6      // Quantidade máxima de power-ups no mapa
#define POWER_UP_TIMEOUT 60.0f    // Tempo de expiração do power-up

#define ENEMY_MAP_LIMIT 6         // Quantidade máxima de inimigos por mapa

// ============================================================================
// 🔄 MODO DE LIMPEZA E COLISÕES
// ============================================================================

#define CLEAN_MODE false
#define ENTITY_COLISION_TOLERANCE 16.0f 

// ============================================================================
// 🎲 EVENTOS ALEATÓRIOS
// ============================================================================

#define RANDOM_EVENT_INTERVAL 10.0f
#define RANDOM_EVENT_INTERVAL_DECREASE 0.25f
#define RANDOM_EVENT_INTERVAL_MINIMUM 5.0f

// Bombas aleatórias
#define RANDOM_BOMB_INITIAL_RADIUS 1
#define RANDOM_BOMB_RADIUS_INCREASE 1
#define RANDOM_BOMB_QUANTITY_INCREASE 1
#define RANDOM_BOMB_INITIAL_QUANTITY 3
#define RANDOM_BOMB_MAP_QUANTITY_INCREASE 3

// Inimigos aleatórios
#define RANDOM_ENEMY_QUANTITY_INCREASE 1
#define RANDOM_ENEMY_INITIAL_QUANTITY 3
#define RANDOM_ENEMY_MAP_QUANTITY_INCREASE 3


// Maquina dando spawn em entidades
# define MACHINE_SPAWN_ANIMATION_TIME 1.0f
# define MACHINE_SPAWN_ANIMATION_TICKS 25
// ============================================================================

#endif
