#include "include/unit.h"
#include "include/unit_struct.h"
#include "include/global_limit.h"
#include "include/army.h"
#include "include/skill.h"
#include "include/battlefield.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int global_unit_pool_count = 0;

Unit *create_and_add_unit(const char *name, int health, int attack, int defence, int range, int travel_speed) {
  if (global_unit_pool_count >= MAX_UNIT_POOL) {
    printf("Global unit pool is full!\n");
    return NULL;
  }

  Unit *unit = (Unit *)malloc(sizeof(Unit));
  if (!unit) {
    printf("Memory allocation failed for unit %s.\n", name);
    return NULL;
  }

  unit->unit_id = global_unit_pool_count;
  strncpy(unit->name, name, sizeof(unit->name) - 1);
  unit->name[sizeof(unit->name) - 1] = '\0';
  unit->position_row = -1;
  unit->position_col = -1;
  unit->stats.health = health;
  unit->stats.max_health = health;
  unit->stats.attack = attack;
  unit->stats.defence = defence;
  unit->stats.range = range;
  unit->stats.travel_speed = travel_speed;

  global_unit_pool[global_unit_pool_count++] = unit;
  return unit;
}

int add_skill_to_unit(Unit *unit, int skill_id) {
  if (unit == NULL) {
    printf("error: Invalid unit reference.\n");
    return -1;
  }

  if (get_skill_by_id(skill_id) == NULL) {
    printf("Error: Skill ID %d does not exit.\n", skill_id);
    return -1;
  }

  for (int i = 0; i < MAX_UNIT_SKILLS; i++) {
    if (unit->skill_list[i] == -1) {
      unit->skill_list[i] = skill_id;
      printf("Added Skill ID %d to Unit %s\n", skill_id, unit->name);
      return 0;
    }
  }

  printf("Error: Unit %s already has the maxium of %d skills.\n", unit->name, MAX_UNIT_SKILLS);
  return -1;
}

Unit *find_unit_by_uid(Battlefield *bf, const char *uid) {
  for (int i = 0; i < ROW_MAX; i++) {
    for (int j = 0; j < COL_MAX; j++) {
      if (bf->grid[i][j] != NULL && strcmp(bf->grid[i][j]->uid, uid) == 0) {
        return bf->grid[i][j];
      }
    }
  }
  return NULL;
}