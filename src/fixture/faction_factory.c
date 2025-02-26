#include "../include/faction.h"
#include "../include/unit_map.h"
#include "../include/world_factory.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void assemble_human_faction(Army army) {
  initialize_faction("Royal Nation", 0);

  // Explicitly assign armies to factions
  if (global_faction_pool[0]) global_faction_pool[0]->army = army;
}

void assemble_creature_faction(Army army) {
  initialize_faction("Woodland Creatures", 1);

  if (global_faction_pool[1]) global_faction_pool[1]->army = army;
}