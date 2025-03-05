#include "../include/army.h"
#include "../include/unit_map.h"
#include "../include/world_factory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void assemble_human_army(Army *army) {
  initialize_army(army, 0);

  for (int unit_id = 0; unit_id < 10; unit_id++) {
    if (add_unit_to_army(army, unit_id, 0) != 0) {
      printf("Fail to add unit ID: %d to armyA.\n", unit_id);
    }
  }
}

void assemble_creature_army(Army *army) {
  initialize_army(army, 1);

  for (int unit_id = 10; unit_id < 20; unit_id++) {
    if (add_unit_to_army(army, unit_id, 0) != 0) {
      printf("Failed to add unit ID: %d to armyB.\n", unit_id);
    }
  }
}