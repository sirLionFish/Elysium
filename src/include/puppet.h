#ifndef PUPPET_H
#define PUPPET_H

#include "battlefield.h"
#include "unit_map.h"
#include "action_queue.h"

void puppet_movement(Battlefield *bf, UnitMap *unit_map, ActionQueue *action_queue);

#endif