#include "../include/puppet.h"
#include "../include/unit_map.h"
#include "../include/battlefield.h"
#include "../include/action_queue.h"
#include "../include/director.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void puppet_movement(Battlefield *bf, UnitMap *unit_map, ActionQueue *action_queue) {
  printf("Starting Puppet Movement for Faction: %d\n", bf->global_turn);

  for (int i = 0; i < HASH_MAP_SIZE; i++) {
    UnitMapEntry *entry = unit_map->table[i];
    while (entry) {
      Unit *actor = entry->unit;
      if (actor == NULL || actor->allegience != bf->global_turn) {
        entry = entry->next;
        continue;
      }

      printf("Calculating movement for UID: %s\n", actor->uid);
      TargetResult result = director_calculate(actor, unit_map);
      const char *target_uid = result.target_uid;

      if (target_uid) {
        Unit *target = get_unit_by_uid(unit_map, target_uid);
        if (target) {
          switch (result.target_status) {
            case TARGET_IN_SKILL_RANGE: {
              printf("Target within range. Executing  action for UID: %s\n", actor->uid);
              Action saved_action = create_execute_action(actor->uid, target->uid, actor->skill_list[1]);
              add_action_to_queue(action_queue, saved_action);
              break;
            }

            case NO_TARGET_IN_SKILL_RANGE: {
              int actor_x = actor->position_row;
              int actor_y = actor->position_col;
              int target_x = target->position_row;
              int target_y = target->position_col;
              int travel_speed = actor->stats.travel_speed;
              int safeguard = 100;

              printf("Unit UID: %s | Target UID: %s | Actor (%d, %d) -> Target (%d, %d)\n",
                actor->uid, target->uid, actor_x, actor_y, target_x, target_y);

              while (travel_speed > 0 && safeguard > 0) {
                int dx = abs(target_x - actor_x);
                int dy = abs(target_y - actor_y);

                if (dx == 0) {
                  int step = (dy >= travel_speed) ? travel_speed : dy;
                  actor_y += (target_y > actor_y) ? step : -step;
                  travel_speed -= step;
                } else if (dy == 0) {
                  int step = (dx >= travel_speed) ? travel_speed : dx;
                  actor_x += (target_x > actor_x) ? step : -step;
                  travel_speed -= step;
                } else {
                  int step_x = (dx >= travel_speed) ? travel_speed : dx;
                  int step_y = (dy >= travel_speed) ? travel_speed : dy;
                  actor_x += (target_x > actor_x) ? step_x : -step_x;
                  actor_y += (target_y > actor_y) ? step_y : -step_y;
                  travel_speed -= (step_x + step_y);
                }

                printf("Current Position: (%d, %d), Remaining Travel Speed: %d\n", actor_x, actor_y, travel_speed);
                if (dx <= 1 && dy <= 1) break;

                safeguard--;
                if (safeguard == 0) {
                  printf("Safeguard triggered: Breaking loop to prevent infinite movement\n");
                  break;
                }
              }
              printf("Final Position: (%d, %d)\n", actor_x, actor_y);
              Action move_action = create_move_action(actor->uid, actor_x, actor_y);
              add_action_to_queue(action_queue, move_action);
              break;
            }
            default: {
              printf("Unexpected Target status for UID: %s\n", actor->uid);
              break;
            }
          }
        } else {
          printf("Target UID %s not found in hash map\n", target_uid);
        }
      } else {
        printf("No target found for UID: %s\n", actor->uid);
      }
      entry = entry->next;
    }
  }
}