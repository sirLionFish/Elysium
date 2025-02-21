#ifndef VALIDATE_H
#define VALIDATE_H

#include "unit.h"
#include "skill.h"
#include "battlefield.h"

int validate_unit(Unit *unit, const char *context);
int validate_skill(Skill *skill);
int validate_target(Unit *actor, Unit *target, Skill *skill);
int validate_position(Battlefield *bf, int row, int col);
int validate_turn(Battlefield *bf, Unit *actor);

#endif