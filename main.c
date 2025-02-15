#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/include/faction.h"
#include "src/include/unit.h"
#include "src/include/army.h"
#include "src/include/battlefield.h"
#include "src/include/movement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/include/faction.h"
#include "src/include/unit.h"
#include "src/include/army.h"
#include "src/include/battlefield.h"
#include "src/include/movement.h"

int main(void) {
    srand((unsigned)time(NULL));

    // -------------------------------
    // Create Units and Build the Global Unit Pool
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

    return 0;
}


