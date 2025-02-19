#include "include/unit.h"
#include "include/skill.h"
#include "include/action.h"
#include "include/movement.h"
#include "include/battlefield.h"
#include "include/global_limit.h"
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

int validate_target(Unit *actor, Unit *target, Skill *skill) {
  if (!actor || !skill) {
    printf("Invalid action: MIssing actor or skill.\n");
    return -1;
  }

  if (!target) {
    printf("Invalid target: Target is NULL for skill %s.\n", skill->name);
    return -2;
  }

  // Simple check: the skill's allegience field indicates the valid target allegience.
  TargetType target_compare =
    (actor->allegience == target->allegience) ? MATCH : NOT_MATCH;
  
  if (skill->target != target_compare) {
  printf("Invalid target: Skill %s requires target match %s, but actor and target comparison is %s.\n",
    skill->name,
    (skill->target == MATCH ? "MATCH" : "NOT_MATCH"),
    (target_compare == MATCH ? "MATCH" : "NOT_MATCH"));
  return -3;
  }
  return 0; 
}

int execute_action(Battlefield *bf, const char *actor_uid, const char *target_uid, int skill_id) {
    // Lookup actor and target using their UIDs
    Unit *actor = find_unit_by_uid(bf, actor_uid);
    if (!actor) {
      printf("ERROR: Actor with UID %s not found on the battlefield.\n", actor_uid);
      return -1;
    }
    
    Unit *target = find_unit_by_uid(bf, target_uid);
    if (!target) {
      printf("ERROR: Target with UID %s not found on the battlefield.\n", target_uid);
      return -2;
    }
    
    // Lookup skill
    Skill *skill = get_skill_by_id(skill_id);
    if (!skill) {
        printf("ERROR: Skill ID %d not found.\n", skill_id);
        return -3;
    }
    
    // Check if it's the actor's faction's turn.
    // For example, if bf->global_turn indicates which allegience is allowed to act:
    if (actor->allegience != bf->global_turn) {
        printf("ERROR: It's not the turn for actor with UID %s (allegience %d, turn %d).\n", 
          actor->uid, actor->allegience, bf->global_turn);
        return -4;
    }
    
    // Check if the target is in range using Chebyshev distance.
    int distance = chebyshev_distance(actor->position_row, actor->position_col, target->position_row, target->position_col);
    if (distance > skill->stat_change.range) {
      printf("ERROR: Target is out of range for skill %s (range: %d, distance: %d).\n", 
        skill->name, skill->stat_change.range, distance);
      return -5;
    }
    
    // Validate target based on skill's allegience requirement.
    int valid = validate_target(actor, target, skill);
    if (valid != 0) {
      printf("ERROR: Target validation failed for skill %s (code: %d).\n", skill->name, valid);
      return valid;
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