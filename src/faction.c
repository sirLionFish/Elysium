#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "include/faction.h"

#define SUCCESS 0
#define ERR_INVALID_POSITION 1
#define ERR_NO_UNIT 2
#define ERR_CELL_OCCUPIED 3
#define ERR_OUT_OF_RANGE 4

Unit create_unit(const char *name, int health, int attack, int defence, int range, int travel_speed) {
  Unit unit;
  strncpy(unit.name, name, sizeof(unit.name));

  unit.stats.health = unit.stats.max_health = health;
  unit.stats.attack = attack;
  unit.stats.defence = defence;
  unit.stats.range = range;
  unit.stats.travel_speed = travel_speed;

  return unit;
}

Skill create_skill(const char *name, int health_change, int attack_change, int defence_change, int range_change, int travel_speed_change) {
  Skill skill;
  strncpy(skill.name, name, sizeof(skill.name));
  skill.stat_change.health = health_change;
  skill.stat_change.attack = attack_change;
  skill.stat_change.defence = defence_change;
  skill.stat_change.range = range_change;
  skill.stat_change.travel_speed = travel_speed_change;
  skill.id = -1; 
  return skill;
}

int add_unit_to_army(Army *army, Unit unit, int row, int col) {
  int ROW_CAPACITY = 10;
  if (row < 0 || row >= ROW_MAX || col < 0 || col >= ROW_CAPACITY) {
    printf("Invalid row or column.\n");
    return 0;
  }

  Row *target_row = &army->rows[row];

  if (target_row->units[col].stats.health > 0) {
    printf("Column %d in Row %d is already occupied.\n", col, row);
    return 0;
  }

  unit.position_row = row;
  unit.position_col = col;
  target_row->units[col] = unit;
  target_row->unit_count++;

  return 1;
}

void add_army_to_row(Army *army, RowType row_type, Unit unit) {
  if (army->rows[row_type].unit_count < 10) {
    army->rows[row_type].units[army->rows[row_type].unit_count++] = unit;
  } else {
    printf("Row is full, cannot add unit: %s\n", unit.name);
  }
}

int move_unit_column(Army *army, int row, int from_col, int to_col) {
  int ROW_CAPACITY = 10;

  if (row < 0 || row >= ROW_MAX || from_col < 0 || from_col >= ROW_CAPACITY || to_col < 0 || to_col >= ROW_CAPACITY) {
    printf("Invalid indices.\n");
    return 0;
  }

  Row *target_row = &army->rows[row];
  Unit *unit_from = &target_row->units[from_col];
  Unit *unit_to = &target_row->units[to_col];

  // Check if there is a unit in the source position
  if (unit_from->stats.health <= 0) {
    printf("No unit in the source column (row: %d, col: %d).\n", row, from_col);
    return 0;
  }

  // Check if target position is occupied
  if (unit_to->stats.health > 0) {
    // Swap the units
    Unit temp = *unit_from;
    *unit_from = *unit_to;
    *unit_to = temp;

    // Update positions
    unit_from->position_col = from_col;
    unit_to->position_col = to_col;

    printf("Swapped %s (Col %d) with %s (Col %d) in Row %d.\n",
      unit_from->name, from_col + 1, unit_to->name, to_col + 1, row + 1);

    return 1;
  }

  // Otherwise, move the unit
  *unit_to = *unit_from;
  unit_to->position_col = to_col;

  // Clear the source position
  *unit_from = (Unit){0};

  printf("Moved %s from Col %d to Col %d in Row %d.\n",
    unit_to->name, from_col + 1, to_col + 1, row + 1);

  return 1;
}

int move_unit_row(Army *army, int from_row, int from_col, int to_row, int to_col) {
  int ROW_MAX = 3;
  int ROW_CAPACITY = 10;
  if (from_row < 0 || from_row >= ROW_MAX || to_row < 0 || to_row >= ROW_MAX || 
    from_col < 0 || from_col >= ROW_CAPACITY || to_col < 0 || to_col >= ROW_CAPACITY) {
    printf("Invalid indices.\n");
    return 0;
  }

  Row *source_row = &army->rows[from_row];
  Row *target_row = &army->rows[to_row];

  // Check if there is a unit in the source position
  if (source_row->units[from_col].stats.health <= 0) {
    printf("No unit in the source column (row: %d, col: %d).\n", from_row, from_col);
    return 0;
  }

  // Check if the target position is empty
  if (target_row->units[to_col].stats.health > 0) {
    printf("Destination column (row: %d, col: %d) is occupied.\n", to_row, to_col);
    return 0;
  }

  // Move the unit
  Unit temp = source_row->units[from_col];
  source_row->units[from_col] = (Unit){0}; // Clear the source position
  source_row->unit_count--;

  temp.position_row = to_row;
  temp.position_col = to_col;

  target_row->units[to_col] = temp;
  target_row->unit_count++;

  printf("Moved %s from row %d, col %d to row %d, col %d.\n",
    temp.name, from_row + 1, from_col + 1, to_row + 1, to_col + 1);

  return 1;
}

void display_battlefield(const Battlefield* battlefield) {
  printf("\nBattlefield:\n");
  for (int i = 0; i < ROWS; i++) {
    printf("Row %d: ", i + 1);
    for (int j = 0; j < COLS; j++) {
      if (battlefield->grid[i][j] != NULL) {
        printf("[%s (%d HP)] ", battlefield->grid[i][j]->name, battlefield->grid[i][j]->stats.health);
      } else {
        printf("[Empty] ");
      }
    }
    printf("\n");
  }
}

void initialize_battlefield(Battlefield *battlefield) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      battlefield->grid[i][j] = NULL;
    }
  }
}

int is_valid_position(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

int is_cell_empty(Battlefield *battlefield, int row, int col) {
  return battlefield->grid[row][col] == NULL;
}

void log_action(const char *action, const Unit *unit, int row, int col) {
  printf("[%s] %s at row %d, col %d\n", action, unit->name, row + 1, col + 1);
}

int place_unit_on_battlefield(Battlefield *battlefield, Unit *unit, int row, int col) {
  if (!is_valid_position(row, col)) {
    printf("Invalid position: row %d, col %d", row, col);
    return ERR_INVALID_POSITION;
  }

  if (!is_cell_empty(battlefield, row, col)) {
    printf("Cell already occupied: row %d, col %d\n", row, col);
    return ERR_CELL_OCCUPIED;
  }

  battlefield->grid[row][col] = unit;
  return SUCCESS;
}

int move_unit(Battlefield *battlefield, int src_row, int src_col, int dest_row, int dest_col) {
  // 1. Validate Input (Essential!)
  if (!is_valid_position(src_row, src_col) || !is_valid_position(dest_row, dest_col)) {
    printf("Invalid move: Source or destination out of bounds.\n");
    return ERR_INVALID_POSITION;
  }

  Unit *unit_to_move = battlefield->grid[src_row][src_col]; // More descriptive name
  if (unit_to_move == NULL) {
    printf("No unit at source position: row %d, col %d\n", src_row + 1, src_col + 1); // +1 for user-friendly display
    return ERR_NO_UNIT;
  }

  if (src_row == dest_row && src_col == dest_col) {
    printf("Unit %s remains in the same position: row %d, col %d\n", unit_to_move->name, src_row + 1, src_col + 1);
    return SUCCESS; // Or perhaps a specific "no move" code
  }

  if (!is_cell_empty(battlefield, dest_row, dest_col)) {
    printf("Destination cell occupied: row %d, col %d\n", dest_row + 1, dest_col + 1);
    return ERR_CELL_OCCUPIED;
  }

  // 2. Perform the Move (Now that validation is complete)
  battlefield->grid[dest_row][dest_col] = unit_to_move; // Move on the grid
  battlefield->grid[src_row][src_col] = NULL;          // Clear the source

  // 3. Update Unit's Internal Position (CRITICAL!)
  unit_to_move->position_row = dest_row;
  unit_to_move->position_col = dest_col;

  log_action("Moved", unit_to_move, dest_row, dest_col);
  return SUCCESS;
}

void apply_action_to_unit(Unit *target, Skill *skill) { 
  if (!target || !skill) return;

  target->stats.health += skill->stat_change.health;
  target->stats.attack += skill->stat_change.attack;
  target->stats.defence += skill->stat_change.defence;
  target->stats.range += skill->stat_change.range;
  target->stats.travel_speed += skill->stat_change.travel_speed;

  if (target->stats.health > target->stats.max_health) {
      target->stats.health = target->stats.max_health;
  }
  if (target->stats.health < 0) {
      target->stats.health = 0;
  }
}

int validate_target(Unit *actor, Unit *target, Skill *skill) {
  if (!actor || !skill) {
    printf("Invalid action: Missing actor or skill.\n");
    return 1;
  }

  if ((skill->action.target != TARGET_SELF) && !target) {
    printf("Invalid target: No target selected for skill %s.\n", skill->name);
    return 2;
  }

  switch (skill->action.target) {
    case TARGET_SELF:
      if (actor != target) {
        printf("Invalid target: skill %s can only used on self.\n", skill->name);
        return 3;
      }
      break;
    case TARGET_ALLY:
      if (actor->allegiance != target->allegiance) {
        printf("Invalid target: %s must be used on allies.\n", skill->name);
        return 4;
      }
      break;
    case TARGET_ENEMY:
      if (actor->allegiance == target->allegiance) {
        printf("Invalid target: %s must be used on enemies\n", skill->name);
        return 5;
      }
      break;
    case TARGET_EVERYONE:
      break; // No restrictions
    default:
      printf("Invalid skill\n");
      return 6;
  }

  return 0; // Success!
}

Skill* get_skill_by_id(int skill_id){
  for(int i = 0; i < MAX_SKILLS; i++){
    if(skill_registry[i].id == skill_id){
      return &skill_registry[i];
    }
  }
  return NULL;
}

void execute_action(Battlefield *battlefield, Unit *actor, int skill_id, int target_row, int target_col) {
  if (!actor) {
    printf("Error: Actor does not exist.\n");
    return;
  }

  Skill *skill = get_skill_by_id(skill_id); // Only call once
  if (!skill) {
    printf("Error: Skill ID %d not found.\n", skill_id);
    return;
  }

  // Range check:
  int dx = abs(target_row - actor->position_row);
  int dy = abs(target_col - actor->position_col);
  int distance = dx + dy; // Manhattan distance (for grid-based movement)

  if (distance > skill->action.range) {
    printf("out of range\n");
    return; // Or return an error code
  }

  Unit *target = battlefield->grid[target_row][target_col];

  if (validate_target(actor, target, skill) != 0) { 
    printf("Invalid target for skill '%s'.\n", skill->name);
    return;
  }

  apply_action_to_unit(target, skill);

  // Log action execution
  printf("%s used '%s' on %s at (%d, %d).\n", actor->name, skill->name, target ? target->name : "empty cell", target_row, target_col);
}

