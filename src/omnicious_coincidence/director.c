#include "../include/director.h"
#include "../include/action.h"
#include "../include/battlefield.h"
#include "../include/unit_struct.h"
#include "../include/unit_map.h"
#include "../include/movement.h"
#include <stddef.h>
#include <limits.h>
#include <stdio.h>

TargetResult director_calculate(Unit *actor, UnitMap *unit_map) {
  TargetResult result;

  result.target_uid = NULL;
  result.target_status = NO_TARGET_IN_SKILL_RANGE;
  result.distance = INF;

  if (!actor) {
    printf("Invalid unit UID\n");
    return result;
  }

  Skill *actor_skill = get_skill_by_id(actor->skill_list[0]);
  TargetType target_type = actor_skill->target;
  Unit *nearest_target = NULL;

  for (int stage = 1; stage <= 3; stage++) {
    result.distance = INF;
    nearest_target = NULL;

    for (int i = 0; i < HASH_MAP_SIZE; i++) {
      UnitMapEntry *entry = unit_map->table[i];
      while (entry) {
        Unit *target = entry->unit;
        if (target) {
          int is_valid_target = 0;
          if ((target_type == MATCH && target->allegience == actor->allegience) ||
              (target_type == NOT_MATCH && target->allegience != actor->allegience)) {
            is_valid_target = 1;
          }

          if (is_valid_target) {
            int distance = 0;
            switch (stage) {
              case 1:
                distance = chebyshev_distance(actor->position_row, actor->position_col, target->position_row, target->position_col);

                if (distance > 0 && distance <= actor_skill->stat_change.range) {
                  result.target_status = TARGET_IN_SKILL_RANGE;
                }
                break;
              case 2:
                distance = manhattan_distance(actor->position_row, actor->position_col, target->position_row, target->position_col);
                break;
              case 3:
                distance = chebyshev_distance(actor->position_row, actor->position_col, target->position_row, target->position_col);
                break;
            }

            if (distance < result.distance) {
              result.distance = distance;
              nearest_target = target;
            }
          }
        }
        entry = entry->next;
      }
    }
    if (nearest_target) break;
  }

  if (nearest_target && nearest_target->uid) {
    printf("Nearest Target: UID %s at (%d, %d) Distance:%d\n",
      nearest_target->uid, nearest_target->position_row, nearest_target->position_col, result.distance);
      result.target_uid = nearest_target->uid;
  } else {
    printf("No valid target found.\n");
  }

  return result;
}