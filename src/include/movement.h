#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "battlefield.h"
#include "unit_struct.h"

  int move_unit(Battlefield *bf, Unit *unit, int dest_row, int dest_col);
  int chebyshev_distance(int r1, int c1, int r2, int c2);
#endif