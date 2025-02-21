#ifndef SKILL_H
#define SKILL_H

#define MAX_SKILLs 100;

#include "global_limit.h"
#include "action.h"
#include "stats.h"

  typedef enum {
    MATCH,
    NOT_MATCH
  } TargetType;

  typedef struct {
    int skill_id;
    char name[20];
    TargetType target;
    Stats stat_change;
  } Skill;

  Skill *get_skill_by_id(int skill_id);
  Skill *create_skill(const char *name, int health, int attack, int defence, int range, int travel_speed, TargetType type);
  Skill global_skill_pool[MAX_SKILLS];
  int global_skill_count;

#endif