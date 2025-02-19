#include "include/skill.h"
#include <string.h>
#include <stdio.h>

int global_skill_count = 0;

Skill *create_skill(const char *name, int health_change, int attack_change, int defence_change, int range_change, int travel_speed, TargetType type) {
  if (global_skill_count >= MAX_SKILLS) {
    printf("Error: Skill pool is full!\n");
    return NULL;
  }

  Skill *skill = &global_skill_pool[global_skill_count];
  skill->skill_id = global_skill_count;
  strncpy(skill->name, name, sizeof(skill->name) - 1);
  skill->name[sizeof(skill->name) - 1] = '\0'; // Ensure null terminate

  skill->stat_change.health = health_change;
  skill->stat_change.attack = attack_change;
  skill->stat_change.defence = defence_change;
  skill->stat_change.range = range_change;
  skill->stat_change.travel_speed = travel_speed;

  skill->target = type;

  global_skill_count++;

  printf("createed skill: id: %d, Name=%s\n", skill->skill_id, skill->name);
  return skill;
}

Skill *get_skill_by_id(int skill_id) {
  if (skill_id < 0 || skill_id >= global_skill_count) {
    printf("Error: invalid skill if %d\n", skill_id);
    return NULL;
  }
  return &global_skill_pool[skill_id];
}