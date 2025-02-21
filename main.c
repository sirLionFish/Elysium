#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/include/faction.h"

int main() {
  Battlefield battlefield;
  initialize_battlefield(&battlefield);

  // 1. Create units
  Unit warrior = create_unit("Warrior", 398, 15, 10, 1, 3);
  warrior.allegiance = ALLEGIANCE_PLAYER; 

  Unit mage = create_unit("Mage", 100, 15, 10, 1, 5);
  mage.allegiance = ALLEGIANCE_PLAYER; 

  Unit goblin = create_unit("Goblin", 50, 10, 5, 1, 2);
  goblin.allegiance = ALLEGIANCE_ENEMY;

  // 2. Place units on the battlefield
  place_unit_on_battlefield(&battlefield, &warrior, 7, 0);  
  place_unit_on_battlefield(&battlefield, &mage, 7, 1);
  place_unit_on_battlefield(&battlefield, &goblin, 0, 0); 

  // 3. Display battlefield
  printf("Initial Battlefield:\n");
  display_battlefield(&battlefield);

  // 4. Move warrior one place forward (up)
  move_unit(&battlefield, 7, 0, 6, 0);
  printf("\nWarrior moved one place forward:\n");
  display_battlefield(&battlefield);

  // 5. Move mage three places forward (up)
  move_unit(&battlefield, 7, 1, 4, 1);
  printf("\nMage moved three places forward:\n");
  display_battlefield(&battlefield);

  // 6. Move warrior one place back (down)
  move_unit(&battlefield, 6, 0, 7, 0);
  printf("\nWarrior moved one place back:\n");
  display_battlefield(&battlefield);

  // 7. Create skill
  for (int i = 0; i < MAX_SKILLS; i++) {
      skill_registry[i].id = -1; // Or some other invalid ID
  }

  // 2. Create skills
  Skill slash = create_skill("Slash", -10, 0, 0, 0, 0);
  slash.id = 0; 
  slash.action.target = TARGET_ENEMY;
  slash.action.range = 2;

  Skill heal = create_skill("Heal", 10, 0, 0, 0, 0);
  heal.id = 1; 
  heal.action.target = TARGET_ALLY; 
  heal.action.range = 1; 

  // 3. Add skills to skill_registry. Keep track of the number of skills.
  int num_skills = 0; // Keep track of the number of skills in the registry
  skill_registry[num_skills++] = slash; // Add to registry
  skill_registry[num_skills++] = heal;  // Add to registry

  // // 8. Move goblin into range of warrior
  move_unit(&battlefield, 0, 0, 6, 0); 
  printf("\nGoblin moved into range:\n");
  display_battlefield(&battlefield);

  // // 9. Warrior uses "Slash" on goblin goblin's position
  execute_action(&battlefield, &warrior, 0, 6, 0);

  // // 10. Display battlefield (and log should be printed by execute_action)
  printf("\nAfter Slash:\n");
  display_battlefield(&battlefield);

  return 0;
}