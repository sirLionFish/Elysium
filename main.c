#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/include/faction.h"
#include "src/include/unit.h"
#include "src/include/army.h"
#include "src/include/battlefield.h"
#include "src/include/movement.h"
#include "src/include/skill.h"

int main(void) {
  srand((unsigned)time(NULL));

  // -------------------------------
  // Create Skills
  // -------------------------------
  Skill *fireball = create_skill("Fireball", 0, 30, 0, 0, 0);
  Skill *ice_shard = create_skill("Ice Shard", 0, 20, 5, 0, 0);
  Skill *heal = create_skill("Heal", 30, 0, 0, 0, 0);
  Skill *shield_bash = create_skill("Shield Bash", 0, 10, 15, 0, 0);

  // -------------------------------
  // Create Units
  // -------------------------------
  for (int i = 0; i < 20; i++) {
    char name[50];
    sprintf(name, "Unit%d", i);
    
    // Create and add unit to the global pool
    Unit *unit = create_and_add_unit(name, 100, 20, 10, 2, 2); 
    if (!unit) {
      printf("Failed to create unit %s.\n", name);
      continue;
    }
    if (!global_unit_pool[i]) {
      printf("Error: Unit %d is NULL, skipping.\n", i);
      continue;
    }
  }

  // -------------------------------
  // Assign Skills to Units
  // -------------------------------
  for (int i = 0; i < 10; i++) {
    if (global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], fireball->skill_id);
      add_skill_to_unit(global_unit_pool[i], ice_shard->skill_id);
    }
  }

  for (int i = 10; i < 20; i++) {
    if (global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], heal->skill_id);
      add_skill_to_unit(global_unit_pool[i], shield_bash->skill_id);
    }
  }

  // -------------------------------
  // Initialize Two Armies and Add Units from Global Unit Pool
  // -------------------------------
  Army armyA, armyB;
  initialize_army(&armyA, 1);
  initialize_army(&armyB, 2);

  for (int i = 0; i < 10; i++) {
    if (add_unit_to_army(&armyA, i, 0) != 0) {
      printf("Failed to add unit with ID %d to armyA.\n", i);
    }
  }
  for (int i = 10; i < 20; i++) {
    if (add_unit_to_army(&armyB, i, 0) != 0) {
      printf("Failed to add unit with ID %d to armyB.\n", i);
    }
  }

  // -------------------------------
  // Initialize Factions and Assign Armies
  // -------------------------------
  initialize_faction("Faction A", 1);
  initialize_faction("Faction B", 2);

  // Explicitly assign armies to factions
  if (global_faction_pool[0]) global_faction_pool[0]->army = armyA;
  if (global_faction_pool[1]) global_faction_pool[1]->army = armyB;

  // -------------------------------
  // Initialize the Battlefield and Add Factions
  // -------------------------------
  Battlefield bf;
  initialize_battlefield(&bf);

  add_faction_to_battlefield(&bf, 0, 0); // Faction A
  add_faction_to_battlefield(&bf, 1, 1); // Faction B

  // -------------------------------
  // Display the Initial Battlefield Grid
  // -------------------------------
  printf("Initial Battlefield Grid:\n");
  display_battlefield(&bf);

  // -------------------------------
  // Move Units
  // -------------------------------
  printf("\nAttempting to move Unit4...\n");
  Unit *unit4 = global_unit_pool[4]; 
  move_unit(&bf, unit4, 1, 1);

  printf("\nAttempting to move Unit10...\n");
  Unit *unit18 = global_unit_pool[18]; 
  move_unit(&bf, unit18, 5, 8);  

  // -------------------------------
  // Display Updated Battlefield
  // -------------------------------
  printf("\nUpdated Battlefield Grid:\n");
  display_battlefield(&bf);

  printf("\nAnd again...\n");
  Unit *secone = global_unit_pool[18]; 
  move_unit(&bf, secone, 4, 8);

  display_battlefield(&bf);

  return 0;
}