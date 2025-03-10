#include "../include/action_queue.h"
#include "../include/action.h"
#include "../include/world_factory.h"
#include "../include/unit_map.h"

void add_move_to_queue(ActionQueue *actionQueue, Action moveAction, UnitMap *unit_map) {
  add_action_to_queue(actionQueue, moveAction, unit_map);
}

void execute_action_to_queue(ActionQueue *actionQueue, Action execAction, UnitMap *unit_map) {
  add_action_to_queue(actionQueue, execAction, unit_map);
}