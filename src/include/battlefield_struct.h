#ifndef BATTLEFIELD_STRUCT_H
#define BATTLEFIELD_STRUCT_H

  #include "faction.h"
  #include "unit_struct.h"

  typedef struct {
    Unit *grid[ROW_MAX][COL_MAX];
    Faction factions[2];
    int global_turn;
  } Battlefield;

#endif