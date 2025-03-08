#include "include/action_queue.h"
#include "include/battlefield.h"
#include "include/unit_map.h"
#include "include/unit_struct.h"
#include "include/action.h"
#include "include/movement.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

Action create_move_action(const char *actor_uid, int dest_row, int dest_col) {
  Action action;
  action.type = ACTION_MOVE;

  //Copy actor's uid
  strncpy(action.params.move.actor_uid, actor_uid, sizeof(action.params.move.actor_uid) - 1);
  action.params.move.actor_uid[sizeof(action.params.move.actor_uid) - 1] = '\0';

  //set the destination coordinates
  action.params.move.dest_row = dest_row;
  action.params.move.dest_col = dest_col;
  return action;
}

Action create_execute_action(const char *actor_uid, const char *target_uid, int skill_id) {
  Action action;
  action.type = ACTION_EXECUTE;

  //Copy actor's UID
  strncpy(action.params.execute.actor_uid, actor_uid, sizeof(action.params.execute.target_uid) - 1);
  action.params.execute.target_uid[sizeof(action.params.execute.target_uid) - 1] = '\0';

  //copy target uid
  strncpy(action.params.execute.target_uid, target_uid, sizeof(action.params.execute.target_uid) - 1);
  action.params.execute.target_uid[sizeof(action.params.execute.target_uid) - 1] = '\0';

  //set skill id
  action.params.execute.skill_id = skill_id;
  return action;
}

int perform_action(Battlefield *bf, UnitMap *unit_map, Action action ){
  int result = 0;
  switch (action.type) {
    case ACTION_MOVE:
      // call move unit function
      result = move_unit(bf, unit_map, action.params.move.actor_uid,
        action.params.move.dest_row, action.params.move.dest_col);
      break;
    
    case ACTION_EXECUTE:
      result = execute_action(bf, unit_map, action.params.execute.actor_uid,
        action.params.execute.target_uid, action.params.execute.skill_id);
      break;
    
    default:
      printf("Unkown action type.\n");
      result = -1;
      break;
  }
  return result;
}

//.......................
//actual queue stuff below
//.......................

void init_action_queue(ActionQueue *queue) {
  queue->actions = malloc(INITIAL_QUEUE_CAPACITY * sizeof (Action));
  if (!queue->actions) {
    printf("Error: Failed to allocate memory for action queue.\n");
    exit(1);
  }
  queue->size = 0;
  queue->capacity = INITIAL_QUEUE_CAPACITY;
}

void add_action_to_queue(ActionQueue *queue, Action action) {
  // resize when needed
  if (queue->size >= queue->capacity) {
    queue->capacity *= 2;
    queue->actions = realloc(queue->actions, queue->capacity * sizeof(Action));
    if (!queue->actions) {
      printf("Error: Failed to allocate memory while resizing action queue.\n");
      exit(1);
    }
  }

  queue->actions[queue->size++] = action;
}

void process_action_queue(ActionQueue *queue, Battlefield *bf, UnitMap *unit_map) {
  for (int i = 0; i < queue->size; i++) {
    perform_action(bf, unit_map, queue->actions[i]);
  }
  queue->size = 0;
}

void print_action_queue(ActionQueue *queue) {
  if (queue->size == 0) {
    printf("Action Queue is empty.\n");
    return;
  }

  printf("Queued Actions (%d):\n", queue->size);
  for (int i = 0; i < queue->size; i++) {
    Action *action = &queue->actions[i];
    if (action->type == ACTION_MOVE) {
      printf("  [%d] Type: %d, Source UID: %s, Dest: (%d, %d)\n",
        i,
        action->type,
        action->params.move.actor_uid,
        action->params.move.dest_row,
        action->params.move.dest_col);
    } else if (action->type == ACTION_EXECUTE) {
      printf("  [%d] Type: %d, Source UID: %s, Target UID: %s, Skill ID: %d\n",
        i,
        action->type,
        action->params.execute.actor_uid,
        action->params.execute.target_uid,
        action->params.execute.skill_id);
    }
  }
}