#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "include/battlefield.h"
#include "include/unit_struct.h"
#include "include/unit_map.h"
#include "include/action_queue.h"

void start_game(Battlefield *bf, int army1_id, int army2_id) {
  bf->global_turn = (rand() % 2 == 0) ? army1_id  : army2_id;
  printf("Game started. Global turn intialized to Army %d.\n", bf->global_turn);
}

void end_turn(Battlefield *bf, int army1_id, int army2_id, ActionQueue *queue, UnitMap *unit_map) {
  process_action_queue(queue, bf, unit_map);

  bf->global_turn = (bf->global_turn == army1_id) ? army2_id : army1_id;
  printf("Turn ended. Now it's %s's turn.\n", bf->factions->name);
}

void select_target(Battlefield *bf, ActionQueue *queue, Unit *actor) {
  int target_x, target_y;

  printf("Select target (x, y) coordinate: ");
  scanf("%d, %d", &target_x, &target_y);

  if (target_x < 0 || target_x >= ROW_MAX || target_y < 0 || target_y >= COL_MAX) {
    printf("Invalid target coordinates.\n");
    return;
  }

  Unit *target_unit = bf->grid[target_x][target_y];

  if (target_unit == NULL) {
    printf("Move action.\n");
    Action action = create_move_action(actor->uid, target_x, target_y);
    add_action_to_queue(queue, action);
  } else {
    printf("Perform action\n");
    int skill_id;
    scanf("%d", &skill_id);
    Action action = create_execute_action(actor->uid, target_unit->uid, skill_id);
    add_action_to_queue(queue, action);
  }
}

void select_actor(Battlefield *bf, ActionQueue *queue, UnitMap *unit_map) {
  char actor_uid[50];
  printf("Select Actor Unit (UID): ");
  scanf("%s", actor_uid);
  // should check if it's unit's turn b4 continuing
  Unit *actor = get_unit_by_uid(unit_map, actor_uid);
  if (actor == NULL) {
    printf("Invalid unit selection.\n");
    return;
  }

  printf("Actor selected: UID %s\n", actor->uid);
  select_target(bf, queue, actor);
}

void game_loop(Battlefield *bf, ActionQueue *queue, UnitMap *unit_map) {
  start_game(bf, 0, 1);
  display_battlefield(bf);
  bool running = true;
  while (running) {
    printf("\nCurrent Army Turn: %d\n", bf->global_turn);
    printf("1. Select Unit\n");
    printf("2. End turn\n");
    printf("3. Quit\n");
    printf("Select Option: ");

    int option;
    scanf("%d", &option);

    switch (option) {
      case 1:
        select_actor(bf, queue, unit_map);
        break;
      case 2:
        end_turn(bf, 0, 1, queue, unit_map);
        display_battlefield(bf);
        break;
      case 3:
        printf("Exiting game...\n");
        running = false;
        break;
      default:
        printf("Invalid option \n");
        break;
    }
  }
}