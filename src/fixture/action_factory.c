// #include "../include/movement.h"
// #include "../include/battlefield.h"
// #include "../include/unit_map.h"
// #include "../include/unit.h"
// #include "../include/skill.h"
// #include "../include/action_queue.h"
// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>

// void simple_move_unit(Battlefield *bf, UnitMap *unit_map, Unit *unit_uid, int dest_row, int dest_col) {
//   Unit *unit = global_unit_pool[4];
//   printf("\nMoving unit %s\n", unit->name);
//   move_unit(bf, unit_map, unit->uid, 4, 8);
// }

// void simple_unit_action(Battlefield *bf, UnitMap *unit_map, Skill skill_id) {
//   int result = execute_action(&bf, &unit_map, global_unit_pool[4]->uid, global_unit_pool[10]->uid, global_skill_pool[1].skill_id);

//   if (result != 0) {
//     printf("execute action failed with error Code: %d\n", result);
//   }
// }



// //revaluate how skill is being called
// Action action_helper_function() {
//   Action execAction = create_execute_action(global_unit_pool[4]->uid, global_unit_pool[10]->uid, global_skill_pool[1].skill_id);
//   return execAction;
// }

// Action move_helper_function() {
//   Action moveAction = create_move_action(global_unit_pool[4]->uid, 6, 3);
//   return moveAction;
// }

// void auto_move_unit(Battlefield *bf, UnitMap unit_map, Action moveAction) {
//   int moveResult = perform_action(&bf, &unit_map, moveAction);

//   if (moveResult != 0) {
//     printf("Failed to move unit Error code: %d\n", moveResult);
//   }
// }

// void adv_unit_action(Battlefield *bf, UnitMap unit_map, Action execAction) {
//   int execResult = perform_action(&bf, &unit_map, execAction);

//   if (execResult != 0) {
//     printf("Failed to act Error code: %d\n", execResult);
//   }
// }