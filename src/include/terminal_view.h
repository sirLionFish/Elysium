#ifndef TERMINAL_view_H
#define TERMINAL_view_H

#include "battlefield.h"
#include "unit_map.h"
#include "action_queue.h"

void render_battlefield(Battlefield *bf);
void game_loop(Battlefield *bf, ActionQueue *queue, UnitMap *unit_map);
void start_game(Battlefield *bf, int army1_id, int army2_id);
void end_turn(Battlefield *bf, int army1_id, int army2_id, ActionQueue *queue, UnitMap *unit_map);


#endif