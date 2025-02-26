#include "../include/skill.h"
#include <string.h>
#include <stdio.h>

void skill_creation() {
              // Name | health | Range | travel_speed | Target_type
  create_skill("Fireball", -10, 8, 0, NOT_MATCH);
  create_skill("Ice Shard", -20, 2, 0, NOT_MATCH);
  create_skill("Heal", 30, 2, 0, MATCH);
  create_skill("Slash", -45, 1, 0, NOT_MATCH);
  create_skill("Cleave", -30, 2, 0, NOT_MATCH);
  create_skill("Speed up", 0, 2, 4, MATCH);
}