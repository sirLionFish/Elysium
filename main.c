#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/include/faction.h"

int main(void) {
    srand((unsigned)time(NULL));
    
    // -------------------------------
    // Create Units and Build a Global Unit Pool
    // -------------------------------
    for (int i = 0; i < 20; i++) {
        char name[50];
        sprintf(name, "Unit%d", i);
        create_unit(name, 100, 20, 10, 1, 1);
    }
    
    // -------------------------------
    // Initialize an Army and Add Units from Global Unit Pool
    // -------------------------------
    Army armyA, armyB;
    initialize_army(&armyA, 1);
    initialize_army(&armyB, 2);
    
    // Add the first 10 units to row 0, and the next 10 to row 1.
    for (int i = 0; i < 10; i++) {
      add_unit_to_army(&armyA, global_unit_pool[i], 0);
    }
    for (int i = 10; i < 20; i++) {
      add_unit_to_army(&armyB, global_unit_pool[i], 0);
    }
    
    // -------------------------------
    // Initialize Factions and Add Them to the Global Faction Pool
    // -------------------------------
    Faction factionA, factionB;
    initialize_faction(&factionA, "Faction A", 1);
    initialize_faction(&factionB, "Faction B", 2);
    
    // For demonstration, assign our filled army to factionA.
    factionA.army = armyA; // Assign the army to faction A
    factionB.army = armyB;
    
    // -------------------------------
    // Initialize the Battlefield and Add Factions
    // -------------------------------
    Battlefield bf;
    initialize_battlefield(&bf);
    
    // Assume factionA is at global faction pool index 0 and factionB at index 1.
    add_faction_to_battlefield(&bf, 0, 0);
    add_faction_to_battlefield(&bf, 1, 1);
    
    // -------------------------------
    // Display the Battlefield Grid
    // -------------------------------
    printf("Battlefield Grid:\n");
    for (int i = 0; i < ROW_MAX; i++) {
        for (int j = 0; j < COL_MAX; j++) {
            if (bf.grid[i][j] != NULL)
                printf("%s ", bf.grid[i][j]->name);
            else
                printf("Empty ");
        }
        printf("\n");
    }
    
    return 0;
}