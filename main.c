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
#include "src/include/unit_map.h"
#include "src/include/action_queue.h"

void start_game(Battlefield *bf, int army1_id, int army2_id) {
  bf->global_turn = (rand() % 2 == 0) ? army1_id : army2_id;
  printf("Game started. Global turn initialized to Army %d.\n", bf->global_turn);
}

void end_turn(Battlefield *bf, int army1_id, int army2_id) {
  bf->global_turn = (bf->global_turn == army1_id) ? army2_id : army1_id;
  printf("Turn ended. Global turn flipped to Army %d.\n", bf->global_turn);
}

int main(void) {
  srand((unsigned)time(NULL));

  // -------------------------------
  // Create Skills and Build the Global Skill Pool
  // -------------------------------
  Skill *fireball = create_skill("Fireball", -10, 30, 0, 8, 0, NOT_MATCH);
  Skill *ice_shard = create_skill("Ice Shard", -20, 20, 5, 2, 0, NOT_MATCH);
  Skill *heal = create_skill("Heal", 30, 0, 0, 2, 0, MATCH);
  Skill *shield_bash = create_skill("Shield Bash", 0, 10, 15, 1, 0, NOT_MATCH);

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
  // For simplicity, assign first 10 units from Army A two offensive skills,
  // and the next 10 units from Army B two defensive/healing skills.
  for (int i = 0; i < 10; i++) {
    if (global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], fireball->skill_id);
      add_skill_to_unit(global_unit_pool[i], ice_shard->skill_id);
      global_unit_pool[i]->allegience = 0;
    }
  }
  for (int i = 10; i < 20; i++) {
    if (global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], heal->skill_id);
      add_skill_to_unit(global_unit_pool[i], shield_bash->skill_id);
      // Assume Army B units have allegience 1.
      global_unit_pool[i]->allegience = 1;
    }
  }

  // -------------------------------
  // Initialize the UnitMap
  // -------------------------------
  // Here we initialize a UnitMap. Global or dynamic allocation is fine.
  // In this case, we declare a local UnitMap which is zero-initialized.
  UnitMap unit_map = {0};

  // -------------------------------
  // Initialize Two Armies and Add Units from Global Unit Pool
  // -------------------------------
  Army armyA, armyB;
  initialize_army(&armyA, 0);
  initialize_army(&armyB, 1);

  // Note: add_unit_to_army is now updated to take an extra parameter UnitMap *.
  for (int i = 0; i < 10; i++) {
    if (add_unit_to_army(&armyA, i, 0, &unit_map) != 0) {
      printf("Failed to add unit with ID %d to armyA.\n", i);
    }
  }
  for (int i = 10; i < 20; i++) {
    if (add_unit_to_army(&armyB, i, 0, &unit_map) != 0) {
      printf("Failed to add unit with ID %d to armyB.\n", i);
    }
  }

  print_unit_map(&unit_map);

  // -------------------------------
  // Initialize Factions and Assign Armies
  // -------------------------------
  initialize_faction("Faction A", 0);
  initialize_faction("Faction B", 1);

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

  // Start the game
  start_game(&bf, 0, 1);

  // -------------------------------
  // Display the Initial Battlefield Grid
  // -------------------------------
  printf("Initial Battlefield Grid:\n");
  display_battlefield(&bf);

  // -------------------------------
  // Create and Add Actions to the Queue
  // -------------------------------
  ActionQueue actionQueue;
  init_action_queue(&actionQueue);
  print_action_queue(&actionQueue);

  // For example, queue a move action for Unit4
  Action moveAction = create_move_action(global_unit_pool[4]->uid, 6, 3);
  add_action_to_queue(&actionQueue, moveAction);
  print_action_queue(&actionQueue);

  // Queue an execute action for Unit4 using fireball on Unit10
  Action execAction = create_execute_action(global_unit_pool[1]->uid, global_unit_pool[10]->uid, fireball->skill_id);
  add_action_to_queue(&actionQueue, execAction);
  print_action_queue(&actionQueue);
  // -------------------------------
  // Process the Action Queue at End of Turn
  // -------------------------------
  // When the faction ends its turn, process all queued actions.
  process_action_queue(&actionQueue, &bf, &unit_map);
  print_action_queue(&actionQueue);

  // -------------------------------
  // Display Updated Battlefield Grid After Processing Actions
  // -------------------------------
  printf("\nUpdated Battlefield Grid After Processing Actions:\n");
  display_battlefield(&bf);

  return 0;
}