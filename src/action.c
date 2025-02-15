// #include "include/unit.h"
// #include "include/skill.h"
// #include "include/action.h"
// #include "include/battlefield.h"
// #include "include/global_limit.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <stddef.h>
// #include <string.h>

// void apply_action_to_unit(Unit *target, Skill *skill) { 
//   if (!target || !skill) return;

//   target->stats.health += skill->stat_change.health;
//   target->stats.attack += skill->stat_change.attack;
//   target->stats.defence += skill->stat_change.defence;
//   target->stats.range += skill->stat_change.range;
//   target->stats.travel_speed += skill->stat_change.travel_speed;

//   if (target->stats.health > target->stats.max_health) {
//     target->stats.health = target->stats.max_health;
//   }
//   if (target->stats.health < 0) {
//     target->stats.health = 0;
//   }
// }

// int validate_target(Unit *actor, Unit *target, Skill *skill) {
//   if (!actor || !skill) {
//     printf("Invalid action: Missing actor or skill.\n");
//     return 1;
//   }

//   if ((skill->action.target != TARGET_SELF) && !target) {
//     printf("Invalid target: No target selected for skill %s.\n", skill->name);
//     return 2;
//   }

//   switch (skill->action.target) {
//     case TARGET_SELF:
//       if (actor != target) {
//         printf("Invalid target: skill %s can only used on self.\n", skill->name);
//         return 3;
//       }
//       break;
//     case TARGET_ALLY:
//       if (actor->allegiance != target->allegiance) {
//         printf("Invalid target: %s must be used on allies.\n", skill->name);
//         return 4;
//       }
//       break;
//     case TARGET_ENEMY:
//       if (actor->allegiance == target->allegiance) {
//         printf("Invalid target: %s must be used on enemies\n", skill->name);
//         return 5;
//       }
//       break;
//     case TARGET_EVERYONE:
//       break; // No restrictions
//     default:
//       printf("Invalid skill\n");
//       return 6;
//   }

//   return 0; // Success!
// }

// Skill* get_skill_by_id(int skill_id){
//   for(int i = 0; i < MAX_SKILLS; i++){
//     if(skill_registry[i].id == skill_id){
//       return &skill_registry[i];
//     }
//   }
//   return NULL;
// }

// void execute_action(Battlefield *battlefield, Unit *actor, int skill_id, int target_row, int target_col) {
//   if (!actor) {
//     printf("Error: Actor does not exist.\n");
//     return;
//   }

//   Skill *skill = get_skill_by_id(skill_id); // Only call once
//   if (!skill) {
//     printf("Error: Skill ID %d not found.\n", skill_id);
//     return;
//   }

//   // Range check:
//   int dx = abs(target_row - actor->position_row);
//   int dy = abs(target_col - actor->position_col);
//   int distance = dx + dy; // Manhattan distance (for grid-based movement)

//   if (distance > skill->action.range) {
//     printf("out of range\n");
//     return; // Or return an error code
//   }

//   Unit *target = battlefield->grid[target_row][target_col];

//   if (validate_target(actor, target, skill) != 0) { 
//     printf("Invalid target for skill '%s'.\n", skill->name);
//     return;
//   }

//   apply_action_to_unit(target, skill);

//   // Log action execution
//   printf("%s used '%s' on %s at (%d, %d).\n", actor->name, skill->name, target ? target->name : "empty cell", target_row, target_col);
// }
