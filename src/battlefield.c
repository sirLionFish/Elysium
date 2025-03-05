#include "include/battlefield.h"
#include "include/faction.h"
#include "include/unit_struct.h"
#include "include/global_limit.h"
#include "include/unit_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void initialize_battlefield(Battlefield *bf) {
  bf->global_turn = rand() % 2;
  for (int i = 0; i < ROW_MAX; i++) {
    for (int j = 0; j < COL_MAX; j++) {
      bf->grid[i][j] = NULL;
    }
  }
}

void add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index, UnitMap *unit_map) {
  if (faction_index < 0 || faction_index > 1) {
    printf("Invalid faction index %d.\n", faction_index);
    return;
  }

  if (faction_id < 0 || faction_id >= global_faction_pool_count || !global_faction_pool[faction_id]) {
    printf("Error: invalid faction_id %d.\n", faction_id);
    return;
  }

  Faction *faction = global_faction_pool[faction_id];
  bf->factions[faction_index] = *faction;

  int row = (faction_index) ? 0 : ROW_MAX - 1;
  int col_offset = 0;

  for (int j = 0; j < faction->army.rows[0].unit_count; j++) {
    Unit *unit = faction->army.rows[0].units[j];

    if (!unit) {
      printf("Warning: NULL unit at index %d for faction %d\n", j, faction_id);
      continue;
    }

    int col = col_offset + j;
    bf->grid[row][col] = unit;
    unit->position_row = row;
    unit->position_col = col;
    insert_unit_to_unit_map(unit_map, unit);

    printf("Placed %s (ID: %d) at (%d, %d)\n", unit->name, unit->unit_id, row, col);
  }
}

void display_battlefield(const Battlefield* battlefield) {
  printf("\nBattlefield:\n");
  for (int i = 0; i < ROW_MAX; i++) {
    printf("Row %d: ", i + 1);
    for (int j = 0; j < COL_MAX; j++) {
      if (battlefield->grid[i][j] != NULL) {
        printf("[%s (%d HP)] ", battlefield->grid[i][j]->name, battlefield->grid[i][j]->stats.health);
      } else {
        printf("[Empty] ");
      }
    }
    printf("\n");
  }
}