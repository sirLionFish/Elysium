#include "include/action_queue.h"
#include "include/battlefield.h"
#include "include/unit_map.h"
#include "include/unit_struct.h"
#include "include/action.h"
#include "include/movement.h"
#include "include/global_limit.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

// void validate_occupied_space()

//.......................
//actual queue stuff below
//.......................

void init_action_queue(ActionQueue *queue) {
  queue->actions = malloc(INITIAL_QUEUE_CAPACITY * sizeof(Action));
  if (!queue->actions) {
    printf("Error: Failed to allocate memory for action queue.\n");
    exit(1);
  }
  queue->size = 0;
  queue->capacity = INITIAL_QUEUE_CAPACITY;
}

void add_action_to_queue(ActionQueue *queue, Action action, UnitMap *unit_map) {
  //resize when needed
  if (queue->size >= queue->capacity) {
    queue->capacity *= 2;
    queue->actions = realloc(queue->actions, queue->capacity * sizeof(Action));
    if (!queue->actions) {
      printf("Error: Failed to allocate memory while resizing action queue.\n");
      exit(1);
    }
  }

  if (action.type == ACTION_MOVE) {
    int action_row = action.params.move.dest_row;
    int action_col = action.params.move.dest_col;
    Unit *current_unit = get_unit_by_uid(unit_map, action.params.move.actor_uid);

    int min_distance;
    int closest_index = -1;

    //check for another move actiuon already targets this spot
    for (int i = 0; i < queue->size; i++) {
      if (queue->actions[i].type == ACTION_MOVE) {
        int existing_row = queue->actions[i].params.move.dest_row;
        int existing_col = queue->actions[i].params.move.dest_col;

        if (existing_row == action_row && existing_col == action_col) {
          Unit *existing_unit = get_unit_by_uid(unit_map, queue->actions[i].params.move.actor_uid);

          int existing_distance = abs(existing_unit->position_row - existing_row) + abs(existing_unit->position_col - existing_col);
          int new_distance = abs(current_unit->position_row - action_row) + abs(current_unit->position_col - action_col);

          if (new_distance < existing_distance) {
            // New unit is closer; mark the existing unit for removal
            min_distance = new_distance;
            closest_index = i;
          } else {
            // New unit is farther; reject the action
            printf("Unit %s move rejected due to collision at (%d, %d)\n", action.params.move.actor_uid, action_row, action_col);
            current_unit->stats.travel_speed += 1;
            return;
          }
        }
      }
    }

    //when a closer unit is found, remove the old action
    if (closest_index != -1) {
      Unit *removed_unit = get_unit_by_uid(unit_map, queue->actions[closest_index].params.move.actor_uid);
      printf("Unit %s overrides Unit %s at (%d, %d)\n", action.params.move.actor_uid, removed_unit->uid, action_row, action_col);
      removed_unit->stats.travel_speed += 1; //refund workaround
      return;
    }
  }

  // Add the action if no conflicts
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
  for (int action_queue_index = 0; action_queue_index < queue->size; action_queue_index++) {
    Action *action = &queue->actions[action_queue_index];
    if (action->type == ACTION_MOVE) {
      printf("[%d] Type: %d, Source UID: %s, Dest: (%d, %d)\n",
        action_queue_index,
        action->type,
        action->params.move.actor_uid,
        action->params.move.dest_row,
        action->params.move.dest_col);
    } else if (action->type == ACTION_EXECUTE) {
      printf("  [%d] Type: %d, Source UID: %s, Target UID: %s, Skill ID: %d\n",
        action_queue_index,
        action->type,
        action->params.execute.actor_uid,
        action->params.execute.target_uid,
        action->params.execute.skill_id);
    }
  }
}