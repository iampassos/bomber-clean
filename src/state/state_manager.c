#include "state_manager.h"
#include "core/assets/asset_manager.h"
#include "state/game_state.h"
#include "state/menu_state.h"

StateManager state_manager = {0};

void state_manager_init() {
  asset_manager_init();

  state_manager_set(STATE_MENU);
}

void state_manager_update() { state_manager.state.update(); }

void state_manager_render() { state_manager.state.render(); }

void state_manager_set(StateType type) {
  switch (type) {
  case STATE_MENU:
    menu_state_init();
    break;
  case STATE_GAME:
    game_state_init();
    break;
  }
}
