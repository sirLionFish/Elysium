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
#include "src/include/world_factory.h"
#include "src/include/terminal_view.h"

int main(void) {
  srand((unsigned)time(NULL));

  // -------------------------------
  // Create Units && Create skill && Assign skill
  // -------------------------------
  assign_skills_for_human_units();
  assign_skills_for_creature_units();

  // -------------------------------
  // Initialize local UnitMap
  // -------------------------------
  UnitMap unit_map = {0};

  // -------------------------------
  // Initialize Two Armies and Add Units from Global Unit Pool
  // -------------------------------
  Army armyA, armyB;
  assemble_human_army(&armyA);
  assemble_creature_army(&armyB);

  // -------------------------------
  // Initialize Factions and Assign Armies
  // -------------------------------
  assemble_human_faction(armyA);
  assemble_creature_faction(armyB);

  // -------------------------------
  // Initialize the Battlefield and Add Factions
  // -------------------------------
  Battlefield bf;
  initialize_battlefield(&bf);

  add_faction_to_battlefield(&bf, 0, 0, &unit_map); // Faction A
  add_faction_to_battlefield(&bf, 1, 1, &unit_map); // Faction B

  print_unit_map(&unit_map);


  // Start the game

  // -------------------------------
  // Create and Add Actions to the Queue
  // -------------------------------
  ActionQueue actionQueue;
  init_action_queue(&actionQueue);
  print_action_queue(&actionQueue);

  game_loop(&bf, &actionQueue, &unit_map);

  return 0;
}