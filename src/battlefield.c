#include "include/battlefield.h"
#include "include/faction.h"
#include "include/unit.h"
#include "include/global_limit.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

UnitMap unit_map[UNIT_MAP_SIZE];

void initialize_battlefield(Battlefield *bf) {
  bf->global_turn = rand() % 2;
  for (int i = 0; i < ROW_MAX; i++) {
    for (int j = 0; j < COL_MAX; j++) {
      bf->grid[i][j] = NULL;
    }
  }
}

// unsigned int hash_uid(const char *str) {
//   unsigned int hash = 5381;
//   int c;
//   while ((c = *str++))
//     hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//   return hash % UNIT_MAP_SIZE;
// }

// void add_unit_to_unitmap(const char *uid, Unit *unit) {
//     unsigned int index = hash_uid(uid);
//     // Linear probing for an empty slot.
//     while (unit_map[index].in_use) {
//         index = (index + 1) % UNIT_MAP_SIZE;
//     }
//     strcpy(unit_map[index].uid, uid);
//     unit_map[index].unit = unit;
//     unit_map[index].in_use = 1;
// }

// Unit *find_unit_by_uid(const char *uid) {
//   unsigned int index = hash_uid(uid);
//   unsigned int start_index = index;
//   while (unit_map[index].in_use) {
//     if (strcmp(unit_map[index].uid, uid) == 0) {
//       return unit_map[index].unit;
//     }
//     index = (index + 1) % UNIT_MAP_SIZE;
//     if (index == start_index) {
//       break; 
//     }
//   }
//   return NULL;
// }

int add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index) {
  if (faction_index < 0 || faction_index > 1) {
    printf("Invalid faction index: %d\n", faction_index);
    return -1;
  }

  if (faction_id < 0 || faction_id >= global_faction_pool_count) {
    printf("Faction ID %d not found in global faction pool.\n", faction_id);
    return -1;
  }

  if (faction_id < 0 || faction_id >= global_faction_pool_count || !global_faction_pool[faction_id]) {
    printf("Error: Invalid faction_id %d.\n", faction_id);
    return -1;
  }

  Faction *faction = global_faction_pool[faction_id];
  bf->factions[faction_index] = *faction;

  int row = (faction_index == 0) ? 0 : ROW_MAX - 1;
  int col_offset = 0;

  for (int j = 0; j < faction->army.rows[0].unit_count; j++) {
    Unit *unit = faction->army.rows[0].units[j];

    // Ensure we are storing the correct unit pointer
    bf->grid[row][col_offset + j] = unit;

    // Also store the unit in UnitMap for fast lookup
    // unit_map[unit->unit_id] = (UnitMap){unit->unit_id, unit, row, col_offset + j};

    printf("Placed %s (ID: %d) at (%d, %d)\n",
           unit->name, unit->unit_id, row, col_offset + j);
  }

  return 0;
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