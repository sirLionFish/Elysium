#include "include/unit.h"
#include "include/unit_struct.h"
#include "include/global_limit.h"
#include "include/battlefield.h"
#include "include/validate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int chebyshev_distance(int r1, int c1, int r2, int c2) {
  int dx = abs(r1 - r2);
  int dy = abs(c1 - c2);
  return (dx > dy) ? dx : dy;
}

int move_unit(Battlefield *bf, const char *unit_uid, int dest_row, int dest_col) {
  //find unit in battlefield
  Unit *unit = find_unit_by_uid(bf, unit_uid);
  if (!unit) {
    printf("Error: Unit with UID %s not found.\n", unit_uid);
    return -1;
  }

  //ensure move with battlefield bounds
  if (validate_position(bf, dest_row, dest_col != 0)) {
    return -2;
  }

  //check unit's turn
  if (validate_turn(bf, unit) != 0) {
    return -3;
  }

  //get unit current position
  int current_row = unit->position_row;
  int current_col = unit->position_col;

  //ensure to not move beyond travel_speed value
  int move_distance = chebyshev_distance(current_row, current_col, dest_row, dest_col);
  if (move_distance > unit->stats.travel_speed) {
    printf("Can't move to %d places, unit's travel speed is %d.\n", unit->stats.travel_speed, move_distance);
    return -4;
  }

  //update unit position on grid
  bf->grid[current_row][current_col] = NULL;
  bf->grid[dest_row][dest_col] = unit;
  unit->position_row = dest_row;
  unit->position_col = dest_col;

  printf("%s moved to (%d, %d)\n", unit->name, dest_row, dest_col);
  return 0;
}