#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include "include/battlefield.h"
#include "include/unit_struct.h"
#include "include/unit_map.h"
#include "include/action_queue.h"
#include "include/skill.h"
#include "include/validate.h"
#include "include/movement.h"

#include "include/director.h"
#include "include/puppet.h"

void select_target(Battlefield *bf, ActionQueue *queue, Unit *actor) {
  int target_x, target_y;

  printf("Select target (x, y) coordinate: ");
  scanf("%d, %d", &target_x, &target_y);

  if (target_x < 0 || target_x >= ROW_MAX || target_y < 0 || target_y >= COL_MAX) {
    printf("Invalid target coordinates.\n");
    return;
  }

  Unit *target_unit = bf->grid[target_x][target_y];

  if (target_unit == NULL) {
    printf("Move action.\n");
    Action action = create_move_action(actor->uid, target_x, target_y);
    add_action_to_queue(queue, action);
  } else {
    printf("Perform action\n");
    int skill_id;
    scanf("%d", &skill_id);
    Action action = create_execute_action(actor->uid, target_unit->uid, skill_id);
    add_action_to_queue(queue, action);
  }
}

void select_actor(Battlefield *bf, ActionQueue *queue, UnitMap *unit_map) {
  char actor_uid[50];
  printf("Select Actor Unit (UID): ");
  scanf("%s", actor_uid);
  // should check if it's unit's turn b4 continuing
  Unit *actor = get_unit_by_uid(unit_map, actor_uid);
  if (actor == NULL) {
    printf("Invalid unit selection.\n");
    return;
  }

  printf("Actor selected: UID %s\n", actor->uid);
  select_target(bf, queue, actor);
}

// const char* director_calculate(Unit *actor, UnitMap *unit_map) { // Expect a Unit pointer
//   if (!actor) {
//     printf("Invalid unit UID\n");
//     return NULL;
//   }

//   printf("Calculating for UID: %s\n", actor->uid);

//   Skill *actor_skill = get_skill_by_id(actor->skill_list[0]);
//   TargetType target_type = actor_skill->target;

//   Unit *nearest_target = NULL;
//   int min_distance = INF;

//   // Stage 1: Search for target within skill range (Primary Priority)
//   for (int i = 0; i < HASH_MAP_SIZE; i++) {
//     UnitMapEntry *entry = unit_map->table[i];
//     while (entry) {
//       Unit *target = entry->unit;
//       if (target) {
//         int is_valid_target = 0;
//         if ((target_type == MATCH && target->allegience == actor->allegience) ||
//             (target_type == NOT_MATCH && target->allegience != actor->allegience)) {
//           is_valid_target = 1;
//         }

//         if (is_valid_target) {
//           int distance = chebyshev_distance(actor->position_row, actor->position_col,
//                                             target->position_row, target->position_col);

//           if (distance > 0 && distance <= actor_skill->stat_change.range) {
//             if (distance < min_distance) {
//               min_distance = distance;
//               nearest_target = target;
//             }
//           }
//         }
//       }
//       entry = entry->next;
//     }
//   }

//   // Stage 2: Fallback to Manhattan Distance (Secondary Priority)
//   if (!nearest_target) {
//     min_distance = INF;  // Reset min_distance
//     for (int i = 0; i < HASH_MAP_SIZE; i++) {
//       UnitMapEntry *entry = unit_map->table[i];
//       while (entry) {
//         Unit *target = entry->unit;
//         if (target) {
//           int is_valid_target = 0;
//           if ((target_type == MATCH && target->allegience == actor->allegience) ||
//               (target_type == NOT_MATCH && target->allegience != actor->allegience)) {
//             is_valid_target = 1;
//           }

//           if (is_valid_target) {
//             int distance = manhattan_distance(actor->position_row, actor->position_col,
//                                               target->position_row, target->position_col);
//             if (distance < min_distance) {
//               min_distance = distance;
//               nearest_target = target;
//             }
//           }
//         }
//         entry = entry->next;
//       }
//     }
//   }

//   // Stage 3: Fallback to Chebyshev Distance (Tertiary Priority)
//   if (!nearest_target) {
//     min_distance = INF;  // Reset min_distance
//     for (int i = 0; i < HASH_MAP_SIZE; i++) {
//       UnitMapEntry *entry = unit_map->table[i];
//       while (entry) {
//         Unit *target = entry->unit;
//         if (target) {
//           int is_valid_target = 0;
//           if ((target_type == MATCH && target->allegience == actor->allegience) ||
//               (target_type == NOT_MATCH && target->allegience != actor->allegience)) {
//             is_valid_target = 1;
//           }

//           if (is_valid_target) {
//             int distance = chebyshev_distance(actor->position_row, actor->position_col,
//                                               target->position_row, target->position_col);
//             if (distance < min_distance) {
//               min_distance = distance;
//               nearest_target = target;
//             }
//           }
//         }
//         entry = entry->next;
//       }
//     }
//   }

//   if (nearest_target) {
//     printf("Nearest Target UID: %s at (%d, %d) Distance: %d\n", nearest_target->uid, nearest_target->position_row, nearest_target->position_col, min_distance);
//     return nearest_target->uid;
//   } else {
//     printf("No valid target found\n");
//     return NULL;
//   }
// }

// void puppet_movement(Battlefield *bf, UnitMap *unit_map, ActionQueue *action_queue) {
//   printf("Start Puppet Movement for Faction: %d\n", bf->global_turn);

//   for (int i = 0; i < HASH_MAP_SIZE; i++) {
//     UnitMapEntry *entry = unit_map->table[i];
//     while (entry) {
//       Unit *actor = entry->unit;
//       if (actor == NULL) {
//         entry = entry->next;
//         continue;
//       }
//       if (actor->allegience != bf->global_turn) {
//         entry = entry->next;
//         continue;
//       }

//       printf("Calculating movement for UID: %s\n", actor->uid);
//       const char *target_uid = director_calculate(actor, unit_map);

//       if (target_uid) {
//         Unit *target = get_unit_by_uid(unit_map, target_uid);
//         if (target) {
//           int actor_x = actor->position_row;
//           int actor_y = actor->position_col;
//           int target_x = target->position_row;
//           int target_y = target->position_col;
//           int travel_speed = actor->stats.travel_speed;

//           printf("Unit UID: %s | Target UID: %s |Actor (%d, %d) -> Target (%d, %d)",
//             actor->uid, target->uid, actor_x, actor_y, target_x, target_y);

//           while (travel_speed > 0) {
//             int dx = abs(target_x - actor_x);
//             int dy = abs(target_y - actor_y);

//             if (dx == 0) {
//               int step = (dy >= travel_speed) ? travel_speed : dy;
//               actor_y += (target_y > actor_y) ? step : -step;
//               travel_speed -= step;
//             } else if (dy == 0) {
//               int step = (dx >= travel_speed) ? travel_speed : dx;
//               actor_x += (target_x > actor_x) ? step : -step;
//               travel_speed -= step;
//             } else {
//               int step_x = (dx >= travel_speed) ? travel_speed : dx;
//               int step_y = (dy >= travel_speed) ? travel_speed : dy;
//               actor_x += (target_x > actor_x) ? step_x : -step_x;
//               actor_y += (target_y > actor_y) ? step_y : -step_y;
//               travel_speed -= (step_x + step_y);
//             }

//             printf("Current Position: (%d, %d), Remaining travel speed: %d\n", actor_x, actor_y, travel_speed);
//             if (dx <= 1 && dy <= 1) break;
//           }
//           printf("Final Position: (%d, %d)\n", actor_x, actor_y);
//           Action moveAction = create_move_action(actor->uid, actor_x, actor_y);
//           add_action_to_queue(action_queue, moveAction);

//         } else {
//           printf("Target UID %s not found in hash map\n", target_uid);
//         }
//       } else {
//         printf("No target found for UID: %s\n", actor->uid);
//       }

//       entry = entry->next;
//     }
//   }
// }

void start_game(Battlefield *bf, int army1_id, int army2_id, UnitMap *unit_map, ActionQueue *action_queue) {
  bf->global_turn = (rand() % 2 == 0) ? army1_id  : army2_id;
  printf("Game started. Global turn intialized to Army %d.\n", bf->global_turn);
  puppet_movement(bf, unit_map, action_queue);
}

void end_turn(Battlefield *bf, int army1_id, int army2_id, ActionQueue *queue, UnitMap *unit_map, ActionQueue *action_queue) {
  process_action_queue(queue, bf, unit_map);

  bf->global_turn = (bf->global_turn == army1_id) ? army2_id : army1_id;
  printf("Turn ended. Now it's %d's turn.\n", bf->global_turn);
  puppet_movement(bf, unit_map, action_queue);
}

void game_loop(Battlefield *bf, ActionQueue *queue, UnitMap *unit_map, ActionQueue *action_queue) {
  start_game(bf, 0, 1, unit_map, action_queue);
  display_battlefield(bf);
  bool running = true;
  while (running) {
    printf("\nCurrent Army Turn: %d\n", bf->global_turn);
    printf("1. Select Unit\n");
    printf("2. End turn\n");
    printf("3. Quit\n");
    printf("Select Option: ");

    int option;
    scanf("%d", &option);

    switch (option) {
      case 1:
        select_actor(bf, queue, unit_map);
        break;
      case 2:
        end_turn(bf, 0, 1, queue, unit_map, action_queue);
        display_battlefield(bf);
        break;
      case 3:
        printf("Exiting game...\n");
        running = false;
        break;
      default:
        printf("Invalid option \n");
        break;
    }
  }
}