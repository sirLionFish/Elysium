#ifndef ARMY_H
#define ARMY_H

#include "global_limit.h"
#include "unit_struct.h"
#include "unit_map.h"

  typedef struct {
    Unit *units[COL_MAX];
    int unit_count;
    int row_formation_id;
  } RowFormation;

  typedef struct {
    int army_id;
    RowFormation rows[ROW_MAX];
  } Army;

  void initialize_army(Army *army, int army_id);
  int add_unit_to_army(Army *army, int unit_id, int formation, UnitMap *unit_map);

#endif