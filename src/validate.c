#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/validate.h"
#include "include/unit_struct.h"
#include "include/skill.h"
#include "include/battlefield.h"

int validate_unit(Unit *unit, const char *context) {
  if (!unit) {
    printf("Error: Invalid in %s\n", context);
    return -1;
  }
  return 0;
}

int validate_skill(Skill *skill) {
  if (!skill) {
    printf("Error: Skill not found\n");
    return -1;
  }
  return 0;
}

int validate_target(Unit *actor, Unit *target, Skill *skill) {
  if (!actor || !skill) {
    printf("Error: Missing actor or skill.\n");
    return -1;
  }

  if (!target) {
    printf("Error: Target is NULL for skill %s\n", skill->name);
    return -2;
  }

  TargetType target_compare = (actor->allegience == target->allegience) ? MATCH : NOT_MATCH;
  if (skill->target != target_compare) {
    printf("Error: Skill %s requires target match %s, but actor and target is a %s\n",
      skill->name,
      (skill->target == MATCH ? "MATCH" : "NOT_MATCH"),
      (target_compare == MATCH ? "MATCH" : "NOT_MATCH"));
    return -3;
  }
  return 0;
}

int validate_position(Battlefield *bf, int row, int col) {
  if (row < 0 || row >= ROW_MAX || col < 0 || col >= COL_MAX) {
    printf("Error: Invalid position (%d, %d).\n", row, col);
    return -1;
  }
  if (bf->grid[row][col] != NULL) {
    printf("Error: Position (%d, %d).\n", row, col);
    return -2;
  }
  return 0;
}

int validate_turn(Battlefield *bf, Unit *actor) {
  if (actor->allegience != bf->global_turn) {
    printf("Error: Not the %s turn (allegiencee %d, turn %d).\n",
      actor->uid, actor->allegience, bf->global_turn);
    return -1;
  }
  return 0;
}