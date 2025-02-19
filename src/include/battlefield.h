#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

  #include "faction.h"
  #include "unit_struct.h"

  typedef struct {
    Unit *grid[ROW_MAX][COL_MAX];
    Faction factions[2];
    int global_turn;
  } Battlefield;

  typedef struct {
    char uid[50];  // key: the unit's unique id string
    Unit *unit;    // pointer to the actual Unit
    int in_use;    // 0 if empty, 1 if occupied
    int position_x;
    int position_y;
  } UnitMap;

  void initialize_battlefield(Battlefield *battlefield);
  int add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index);
  void display_battlefield(const Battlefield* battlefield);
  // void add_unit_to_unitmap(const char *uid, Unit *unit);
#endif