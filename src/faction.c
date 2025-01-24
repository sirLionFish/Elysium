#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "include/faction.h"

Unit create_unit(const char *name, int health, int attack, int defense, int range, int speed, int special_ability) {
  Unit unit;
  strncpy(unit.name, name, sizeof(unit.name));

  unit.health = unit.max_health = health;
  unit.attack = attack;
  unit.defense = defense;
  unit.range = range;
  unit.speed = speed;
  unit.special_ability = special_ability;

  return unit;
}

void add_unit_to_row(Army *army, RowType row_type, Unit unit) {
  if (army->rows[row_type].unit_count < 10) {
    army->rows[row_type].units[army->rows[row_type].unit_count++] = unit;
  } else {
    printf("Row is full, cannot add unit:%s\n", unit.name);
  }
}

int calculate_army_score(const Army *army) {
  int score = 0;

  for (int row = 0; row < ROW_MAX; row++) {
    for (int i = 0; i < army->rows[row].unit_count; i++) {
      Unit unit = army->rows[row].units[i];
      score += unit.attack + unit.defense + unit.health;
    }
  }

  return score;
}

// Army create_army(int unit_count) {
//   Army army;
//   army.units = (Unit *)malloc(sizeof(Unit) * unit_count);
//   army.unit_count = unit_count;
//   return army;
// }

// void destroy_army(Army *army) {
//   free(army->units);
//   army->units = NULL;
//   army->unit_count = 0;
// }

// void display_army(const Army *army) {
//   printf("Army with %d units:\n", army->unit_count);
//   for (int i = 0; i < army->unit_count; i++) {
//     Unit unit = army->units[i];
//     printf(" Unit  %d: %s (HP: %d/%d, ATK: %d, DEF: %d, SPD: %d)\n", 
//     i + 1, unit.name, unit.health, unit.max_health, unit.attack, unit.defense, unit.speed);
//   }
// }