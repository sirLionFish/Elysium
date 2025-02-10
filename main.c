#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/include/faction.h"

int main(void) {
  for (int i = 0; i < 20; i++) {
    char name[50];
    sprintf(name, "Unit%d", i);
    create_unit(name, 100, 20, 10, 1, 1);
  }

  Army army;
  initialize_army(&army, 1);

  for (int i = 0; i < 10; i++) {
    add_unit_to_army(&army, global_unit_pool[i], 0);
  }
  for (int i = 10; i < 20; i++) {
    add_unit_to_army(&army, global_unit_pool[i], 1);
  }

  // Display the army's formation.
  printf("Army ID: %d\n", army.army_id);
  for (int i = 0; i < ROW_MAX; i++) {
    printf("Row %d (units: %d): ", i, army.rows[i].unit_count);
    for (int j = 0; j < army.rows[i].unit_count; j++) {
      printf("%s ", army.rows[i].units[j].name);
    }
    printf("\n");
  }

  return 0;
}