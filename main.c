#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/include/faction.h"

int main() {




// OR if every member requires explicit init:

Army army1 = { .total_score = 0 };
for (int i = 0; i < ROW_MAX; i++) {
    army1.rows[i].unit_count = 0; // Initialize the unit count for each row
    for (int j = 0; j < 10; j++) {
        // Initialize each Unit in the row
        army1.rows[i].units[j] = (Unit){0};
    }
}

Army army2 = { .total_score = 0 };
for (int i = 0; i < ROW_MAX; i++) {
    army2.rows[i].unit_count = 0;
    for (int j = 0; j < 10; j++) {
        army2.rows[i].units[j] = (Unit){0};
    }
}

  //create unit
  Unit warrior = create_unit("Warrior", 100, 15, 10, 1, 5, 0);
  Unit archer = create_unit("archer", 100, 15, 10, 1, 5, 0);
  Unit mage = create_unit("mage", 100, 15, 10, 1, 5, 0);
  Unit knight = create_unit("Knight", 100, 15, 10, 1, 5, 0);
  Unit spearman = create_unit("spearman", 100, 15, 10, 1, 5, 0);

  // Add units to rows
  add_unit_to_row(&army1, ROW_MELEE, warrior);
  add_unit_to_row(&army1, ROW_RANGED, archer);
  add_unit_to_row(&army1, ROW_MAGIC, mage);

  add_unit_to_row(&army2, ROW_MELEE, knight);
  add_unit_to_row(&army2, ROW_RANGED, spearman);

  army1.total_score = calculate_army_score(&army1);
  army2.total_score = calculate_army_score(&army2);

  printf("Army 1 score: %d\n", army1.total_score);
  printf("Army 2 score: %d\n", army2.total_score);

  //determine winner
  if (army1.total_score > army2.total_score) {
    printf("Army 1 wins\n");
  } else if (army1.total_score < army2.total_score) {
    printf("Army2 wins\n");
  } else {
    printf("it's a tie\n");
  }





  // Army army1 = create_army(3);
  // Army army2 = create_army(2);

  // army1.units[0] = create_unit("Warrior", 100, 15, 10, 1, 5, 0);
  // army1.units[1] = create_unit("Archer", 75, 10, 10, 1, 5, 0);
  // army1.units[2] = create_unit("Mage", 50, 15, 10, 1, 5, 0);

  // army2.units[0] = create_unit("Knight", 120, 18, 12, 1, 4, 0);
  // army2.units[1] = create_unit("Spearman", 90, 14, 2, 1, 6, 0);

  // printf("Army 1:\n");
  // display_army(&army1);

  // printf("\nArmy 2:\n");
  // display_army(&army2);

  // destroy_army(&army1);
  // destroy_army(&army2);

  return 0;
}