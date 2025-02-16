#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "include/army.h"
#include "include/unit.h"
#include "include/global_limit.h"
#include "include/battlefield.h"

void initialize_army(Army *army, int army_id) {
  army->army_id = army_id;
  for (int i = 0; i < ROW_MAX; i++) {
    army->rows[i].unit_count = 0;

    //initialize unit slot to empty in the row
    for (int j = 0; j < COL_MAX; j++) {
      army->rows[i].units[j] = NULL;
    }
  }
}


void assign_unit_uid(Unit *unit, int army_id, int position) {
  sprintf(unit->uid, "%s:%X:%X", unit->name, army_id, position);
}

int add_unit_to_army(Army *army, int unit_id, int formation) {
    if (formation < 0 || formation >= ROW_MAX) {
        printf("Invalid row formation id: %d\n", formation);
        return -1;
    }

    if (unit_id < 0 || unit_id >= global_unit_pool_count) {
        printf("Unit ID %d not found in global unit pool.\n", unit_id);
        return -1;
    }

    RowFormation *row = &army->rows[formation];
    if (row->unit_count >= COL_MAX) {
        printf("Row %d is full.\n", formation);
        return -1;
    }

    Unit *unit = global_unit_pool[unit_id];

    // Assign unit to the formation, but DO NOT set battlefield position yet
    row->units[row->unit_count] = unit;

    // Update the unit's UID
    assign_unit_uid(unit, army->army_id, row->unit_count);

    row->unit_count++;

    printf("Added Unit %s (ID: %d, UID: %s) to Army %d in Formation Row %d (Pending Deployment)\n", 
           unit->name, unit->unit_id, unit->uid, army->army_id, formation);

    return 0; 
}




// int add_unit_to_army(Army *army, Unit unit, int formation) {
//   if (row_formation_id < 0 || row_formation_id >= ROW_MAX) {
//     printf("Invalid row formation id: %d\n", row_formation_id);
//     return -1;
//   }
//   RowFormation *row = &army->rows[row_formation_id];
//   if (row->unit_count >= COL_MAX) {
//     printf("Row %d is full.\n", row_formation_id);
//     return -1;
//   }
//   // Set the unit's position.
//   unit.position_row = row_formation_id;
//   unit.position_col = row->unit_count;
//   // Assign a UID to the unit (using army id and its position in that row).
//   assign_unit_uid(&unit, army->army_id, row->unit_count);
//   // Add the unit to the row.
//   row->units[row->unit_count] = unit;
//   row->unit_count++;
//   return 0;
// }