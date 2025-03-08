#include "../include/unit.h"
#include "../include/skill.h"
#include "../include/world_factory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// -------------------------------
// Create Units
// -------------------------------
void assemble_human_units() {
                   // name, health, range, travel_speed
  create_and_add_unit("Farmer", 100, 2, 1);
  create_and_add_unit("Guard", 100, 2, 2);
  create_and_add_unit("Peasant", 100, 2, 2);
  create_and_add_unit("Merchant", 100, 2, 1);
  create_and_add_unit("Knight", 100, 2, 2);
  create_and_add_unit("Monk", 100, 2, 1);
  create_and_add_unit("Priest", 100, 2, 2);
  create_and_add_unit("Mage", 100, 2, 1);
  create_and_add_unit("Mercenary", 100, 2, 2);
  create_and_add_unit("Thieve", 100, 2, 3);
}

void assemble_creature_units() {
  create_and_add_unit("Globlin", 100, 2, 1);
  create_and_add_unit("Troll", 100, 2, 2);
  create_and_add_unit("Gremlin", 100, 2, 3);
  create_and_add_unit("Zombie", 100, 2, 3);
  create_and_add_unit("Vampire", 100, 2, 2);
  create_and_add_unit("Wolf", 100, 2, 1);
  create_and_add_unit("Bear", 100, 2, 2);
  create_and_add_unit("Orc", 100, 2, 1);
  create_and_add_unit("Demon", 100, 2, 1);
  create_and_add_unit("Cultist", 100, 2, 1);
}

// -------------------------------
// Add skill to unit for Human units
// -------------------------------
void assign_skills_for_human_units() {
  assemble_human_units();
  skill_creation(); // is defined in skill_factory.c

  Skill *fireball = get_skill_by_id(1);
  add_skill_to_unit(global_unit_pool[1], fireball->skill_id);

  int num_skills = 6;
  int num_units = 10;

  for (int i = 0; i < num_units; i++) {
    int skill_id = (i % num_skills) + 1;
    Skill *skill = get_skill_by_id(skill_id);

    if (skill && global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], skill->skill_id);
    } else {
      printf("Error: Skill or Unit is NULL for unit %d, skill id %d\n", i, skill_id);
    }
  }
}

// -------------------------------
// Add skill to unit for creature units
// -------------------------------
void assign_skills_for_creature_units() {
  assemble_creature_units();
  skill_creation();

  int num_skills = 6;
  int num_units = 10;

  for (int i = 0; i < num_units; i++) {
    int skill_id = (i % num_skills) + 1;
    Skill *skill = get_skill_by_id(skill_id);

    if (skill && global_unit_pool[i]) {
      add_skill_to_unit(global_unit_pool[i], skill->skill_id);
    } else {
      printf("Error: Skill or Unit is NULL for unit %d, skill id %d\n", i, skill_id);
    }
  }
}