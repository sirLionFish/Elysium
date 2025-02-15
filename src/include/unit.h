#ifndef UNIT_H
#define UNIT_H

#include "global_limit.h"
#include "skill.h"

  typedef enum {
    Class_MELEE,
    Class_RANGE,
    Class_MAGIC,
    Class_MAX
  } ClassType;

  typedef enum {
    ALLEGIANCE_PLAYER,
    ALLEGIANCE_ENEMY
  } Allegiance;

  typedef enum {
    RANGE_CLASS,
    MELEE,
    DEFENSE,
    RANGE_MELEE,
    MELEE_DEFENSE,
    RANGE_DEFENCE,
    RANGE_MELEE_DEFENCE
  } Class;

  typedef struct {
    int health;
    int max_health;
    int attack;
    int defence;
    int range;
    int travel_speed;
  } Stats;

  typedef struct {
    int unit_id;
    char uid[50];
    char name[50];
    int position_row;
    int position_col;
    Allegiance allegiance;
    Stats stats;
    // Skill skills;
  } Unit;


  Unit *global_unit_pool[MAX_UNIT_POOL];
  Unit *create_and_add_unit(const char *name, int health, int attack, int defence, int range, int travel_speed);
  int global_unit_pool_count;

#endif