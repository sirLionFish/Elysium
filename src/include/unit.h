#ifndef UNIT_H
#define UNIT_H

#include "global_limit.h"
#include "battlefield.h"
#include "unit_struct.h"

  Unit *global_unit_pool[MAX_UNIT_POOL];
  Unit *create_and_add_unit(const char *name, int health, int attack, int defence, int range, int travel_speed);
  int global_unit_pool_count;
  int add_skill_to_unit(Unit *unit, int skill_id);
  Unit *find_unit_by_uid(Battlefield *bf, const char *uid);

#endif