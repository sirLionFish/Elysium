#include "include/unit.h"
#include "include/global_limit.h"
#include "include/battlefield.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


int chebyshev_distance(int r1, int c1, int r2, int c2) {
  int dx = abs(r1 - r2);
  int dy = abs(c1 - c2);
  return (dx > dy) ? dx : dy;
}

int move_unit(Battlefield *bf, Unit *unit, int dest_row, int dest_col) {
  int found = 0;
  int current_row = -1, current_col = -1;

  // Search for the unit using UID comparison instead of name comparison
  for (int i = 0; i < ROW_MAX; i++) {
    for (int j = 0; j < COL_MAX; j++) {
      if (bf->grid[i][j] != NULL && strcmp(bf->grid[i][j]->uid, unit->uid) == 0) {
        current_row = i;
        current_col = j;
        found = 1;
        break;
      }
    }
    if (found) break;
  }

  // If unit not found, print error
  if (!found) {
    printf("ERROR: Unit with UID %s not found on the battlefield.\n", unit->uid);
    return -1;
  }

  printf("Unit %s (UID: %s) found at (%d, %d). Attempting to move to (%d, %d)\n",
         unit->name, unit->uid, current_row, current_col, dest_row, dest_col);

  // Ensure move is within battlefield bounds
  if (dest_row < 0 || dest_row >= ROW_MAX || dest_col < 0 || dest_col >= COL_MAX) {
    printf("Invalid destination: (%d, %d)\n", dest_row, dest_col);
    return -1;
  }

  // Ensure the unit doesn't move more than its travel speed
  int move_distance = chebyshev_distance(current_row, current_col, dest_row, dest_col);
  if (move_distance > unit->stats.travel_speed) {
    printf("Unit %s (UID: %s) can't move that far (speed: %d, attempted: %d).\n",
           unit->name, unit->uid, unit->stats.travel_speed, move_distance);
    return -1;
  }

  // Ensure the destination is empty
  if (bf->grid[dest_row][dest_col] != NULL) {
    printf("Destination (%d, %d) is occupied.\n", dest_row, dest_col);
    return -1;
  }

  // Move the unit
  bf->grid[current_row][current_col] = NULL;
  bf->grid[dest_row][dest_col] = unit;

  printf("Unit %s (UID: %s) moved to (%d, %d)\n", unit->name, unit->uid, dest_row, dest_col);
  return 0;
}