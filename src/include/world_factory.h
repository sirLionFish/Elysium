#ifndef WORLD_FACTORY_H
#define WORLD_FACTORY_H

#include "unit_map.h"
#include "army.h"
#include "action_queue.h"

  void skill_creation();
  void assemble_human_units();
  void assemble_creature_units();
  
  void assign_skills_for_human_units();
  void assign_skills_for_creature_units();

  void assemble_human_army(Army *army);
  void assemble_creature_army(Army *army);

  void assemble_human_faction(Army army);
  void assemble_creature_faction(Army army);

  void add_move_to_queue(ActionQueue *actionQueue, Action moveAction, UnitMap *unit_map);
#endif