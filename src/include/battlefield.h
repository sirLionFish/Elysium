#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

  #include "faction.h"
  #include "unit_struct.h"

  typedef struct {
    Unit *grid[ROW_MAX][COL_MAX];
    Faction factions[2];
    int global_turn;
  } Battlefield;

  void initialize_battlefield(Battlefield *battlefield);
  int add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index);
  void display_battlefield(const Battlefield* battlefield);
  
#endif