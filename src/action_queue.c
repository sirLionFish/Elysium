#include "include/action_queue.h"
#include "include/battlefield.h"
#include "include/unit_map.h"
#include "include/action.h"
#include "include/movement.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


Action create_move_action(const char *actor_uid, int dest_row, int dest_col) {
  Action action;
  action.type = ACTION_MOVE;

  //Copy actot's uid
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