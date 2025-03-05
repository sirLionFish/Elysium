#include "include/unit.h"
#include "include/unit_struct.h"
#include "include/global_limit.h"
#include "include/battlefield.h"
#include "include/validate.h"
#include "include/unit_map.h"
#include "include/action.h"
#include "include/action_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int chebyshev_distance(int r1, int c1, int r2, int c2) {
  int dx = abs(r1 - r2);
  int dy = abs(c1 - c2);
  return (dx > dy) ? dx : dy;
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

int move_unit(Battlefield *bf, UnitMap *unit_map, const char *unit_uid, int dest_row, int dest_col) {
  // Use the UID to look up the unit in the hash map.
  Unit *unit = get_unit_by_uid(unit_map, unit_uid);
  if (!unit) {
    printf("Error: Unit with UID %s not found in move_unit.\n", unit_uid);
    return -1;
  }
  
  // Validate that the destination is within the battlefield bounds.
  if (validate_position(bf, dest_row, dest_col) != 0) {
    printf("Error: Invalid move position (%d, %d).\n", dest_row, dest_col);
    return -2;
  }
  
  // Ensure that it is currently the unit's turn.
  if (validate_turn(bf, unit) != 0) {
    printf("Error: It's not %s's turn.\n", unit->name);
    return -3;
  }
  
  // Get the unit's current position.
  int current_row = unit->position_row;
  int current_col = unit->position_col;
  
  // Calculate the distance the unit is trying to move.
  int move_distance = chebyshev_distance(current_row, current_col, dest_row, dest_col);
  if (move_distance > unit->stats.travel_speed) {
    printf("Error: %s cannot move %d spaces; max allowed is %d.\n", unit->name, move_distance, unit->stats.travel_speed);
    return -4;
  }
  
  // Update the battlefield grid: remove the unit from its current position...
  bf->grid[current_row][current_col] = NULL;
  bf->grid[dest_row][dest_col] = unit;
  
  // Update the unit's stored position.
  unit->position_row = dest_row;
  unit->position_col = dest_col;
  
  printf("%s moved to (%d, %d)\n", unit->name, dest_row, dest_col);
  return 0;
}