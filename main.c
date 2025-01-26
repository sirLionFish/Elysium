#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/include/faction.h"

int main() {
  Battlefield battlefield;
  initialize_battlefield(&battlefield);

  // Create units
  Unit warrior = create_unit("Warrior", 398, 15, 10, 1, 3, 0);
  Unit mage = create_unit("mage", 100, 15, 10, 1, 5, 0);

  // Add units to the army
  place_unit_on_battlefield(&battlefield, &warrior, 0, 0); // Player 1, bottom row
  place_unit_on_battlefield(&battlefield, &mage, 2, 2);

  display_battlefield(&battlefield);

    move_unit(&battlefield, 2, 2, 1, 2);

    // Test invalid moves
    move_unit(&battlefield, 0, 0, 4, 0);  // Out of range
    move_unit(&battlefield, 0, 0, 0, 0);  // Same position
    move_unit(&battlefield, 0, 0, 1, 2);

  display_battlefield(&battlefield);

  return 0;
}