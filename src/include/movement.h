#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "battlefield.h"
#include "unit_struct.h"

  int move_unit(Battlefield *bf, UnitMap *unit_map, const char *unit_uid, int dest_row, int dest_col);
  int chebyshev_distance(int r1, int c1, int r2, int c2);
  int manhattan_distance(int x1, int y1, int x2, int y2);
#endif