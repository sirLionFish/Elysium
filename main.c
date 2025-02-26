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

void start_game(Battlefield *bf, int army1_id, int army2_id) {
  bf->global_turn = (rand() % 2 == 0) ? army1_id : army2_id;
  printf("Game started. Global turn initialized to Army %d.\n", bf->global_turn);
}

void end_turn(Battlefield *bf, int army1_id, int army2_id, ActionQueue *queue, UnitMap *unit_map) {
  //process queued actions
  process_action_queue(queue, bf, unit_map);

  //flip global turn
  bf->global_turn = (bf->global_turn == army1_id) ? army2_id : army1_id;
  printf("Turn ended. Gloabal turn flipped to Army %d.\n", bf->global_turn);
}

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
  assemble_human_army(&armyA, &unit_map);
  assemble_creature_army(&armyB, &unit_map);

  print_unit_map(&unit_map);

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

  // Queue a move action for Unit4
  Action moveAction = create_move_action(global_unit_pool[4]->uid, 6, 3);
  add_move_to_queue(&actionQueue, moveAction);

  // Queue an execute action for Unit4 using ice shard on Unit10 (shoud be out of range)
  Action execAction = create_execute_action(global_unit_pool[1]->uid, global_unit_pool[10]->uid, global_skill_pool[1].skill_id);
  add_action_to_queue(&actionQueue, execAction);
  print_action_queue(&actionQueue);

  // -------------------------------
  // Process the Action Queue at End of Turn
  // -------------------------------
  // When the faction ends its turn, process all queued actions.
  end_turn(&bf, 0, 1, &actionQueue, &unit_map);
  print_action_queue(&actionQueue);

  // -------------------------------
  // Display Updated Battlefield Grid After Processing Actions
  // -------------------------------
  printf("\nUpdated Battlefield Grid After Processing Actions:\n");
  display_battlefield(&bf);

  return 0;
}