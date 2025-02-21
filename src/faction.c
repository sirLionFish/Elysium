#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "include/faction.h"
#include "include/unit.h"
#include "include/army.h"

int global_faction_pool_count = 0; 


void initialize_faction(const char *name, int army_id) {
  if (global_faction_pool_count >= MAX_FACTIONS) {
    printf("Global faction pool is full!\n");
    return;
  }
  
  Faction *new_faction = (Faction *)malloc(sizeof(Faction));
  if (!new_faction) {
    printf("Memory allocation failed for faction %s.\n", name);
    return;
  }

  strncpy(new_faction->name, name, sizeof(new_faction->name) - 1);
  new_faction->name[sizeof(new_faction->name) - 1] = '\0';
  initialize_army(&new_faction->army, army_id);


  global_faction_pool[global_faction_pool_count++] = new_faction;
}

void display_faction(const Faction *faction) {
  printf("\n-- %s --\n", faction->name);
  for (int row = 0; row < ROW_MAX; row++) {
    printf("Row %d", row + 1);
    for (int col = 0; col < COL_MAX; col++) {
      const Unit *unit = faction->army.rows[row].units[col];
      if (unit->stats.health > 0)
        printf("[%s: %d hp]", unit->name, unit->stats.health);
      else
        printf("[Empty]");
    }
    printf("\n");
  }

}
