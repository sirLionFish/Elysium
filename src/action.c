#include "include/unit.h"
#include "include/skill.h"
#include "include/action.h"
#include "include/movement.h"
#include "include/battlefield.h"
#include "include/global_limit.h"
#include "include/validate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void apply_action_to_unit(Unit *target, Skill *skill) { 
  if (!target || !skill) return;

  // Apply skill stat changes to the target's stats.
  target->stats.health += skill->stat_change.health;
  target->stats.attack += skill->stat_change.attack;
  target->stats.defence += skill->stat_change.defence;
  target->stats.range += skill->stat_change.range;
  target->stats.travel_speed += skill->stat_change.travel_speed;

  // Clamp health so that it does not exceed max_health or drop below 0.
  if (target->stats.health > target->stats.max_health) {
    target->stats.health = target->stats.max_health;
  }
  if (target->stats.health < 0) {
    target->stats.health = 0;
  }
}

int execute_action(Battlefield *bf, const char *actor_uid, const char *target_uid, int skill_id) {
  // Validate checks
  Unit *actor = find_unit_by_uid(bf, actor_uid);
  Unit *target = find_unit_by_uid(bf, target_uid);
  Skill *skill = get_skill_by_id(skill_id);

  if (validate_unit(actor, "execute_action (actor)") != 0 ||
    validate_unit(target, "execute_action (target)") != 0 ||
    validate_skill(skill) != 0 ||
    validate_turn(bf, actor) != 0 ||
    validate_target(actor, target, skill) != 0
  ) {return -1;}
  
  // Check if the target is in range using Chebyshev distance.
  int distance = chebyshev_distance(actor->position_row, actor->position_col, target->position_row, target->position_col);
  if (distance > skill->stat_change.range) {
    printf("ERROR: Target is out of range for skill %s (range: %d, distance: %d).\n", 
      skill->name, skill->stat_change.range, distance);
    return -2;
  }
  
  // If all checks pass, apply the skill's stat changes to target's stats.
  apply_action_to_unit(target, skill);
  
  // Log action execution.
  printf("%s used '%s' on %s at (%d, %d).\n", 
    actor->uid, skill->name, target->uid, target->position_row, target->position_col);
  printf("Updated target stats: Health=%d, Attack=%d, Defence=%d, Range=%d, Travel Speed=%d\n",
    target->stats.health, target->stats.attack, target->stats.defence,
    target->stats.range, target->stats.travel_speed);
  
  return 0;
}