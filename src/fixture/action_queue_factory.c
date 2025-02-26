#include "../include/action_queue.h"
#include "../include/action.h"
#include "../include/world_factory.h"

void add_move_to_queue(ActionQueue *actionQueue, Action moveAction) {
  add_action_to_queue(actionQueue, moveAction);
}

void execute_action_to_queue(ActionQueue *actionQueue, Action execAction) {
  add_action_to_queue(actionQueue, execAction);
}