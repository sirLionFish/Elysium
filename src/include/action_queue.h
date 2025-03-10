#ifndef ACTION_QUEUE_H
#define ACTION_QUEUE_H

#include "battlefield.h"
#include "unit_map.h"

typedef enum {
  ACTION_MOVE,
  ACTION_EXECUTE
} ActionType;

typedef struct {
  char actor_uid[50];
  int dest_row;
  int dest_col;
} MoveParams;

typedef struct {
  char actor_uid[50];
  char target_uid[50];
  int skill_id;
} ExecuteParams;

typedef struct {
  ActionType type;
  union {
    MoveParams move;
    ExecuteParams execute;
  } params;
} Action;

typedef struct {
  Action *actions;
  int size;
  int capacity;
} ActionQueue;

int perform_action(Battlefield *bf, UnitMap *unit_map, Action action);
Action create_move_action(const char *actor_uid, int dest_row, int dest_col);
Action create_execute_action(const char *actor_uid, const char *target_uid, int skill_id);
void init_action_queue(ActionQueue *queue);
void process_action_queue(ActionQueue *queue, Battlefield *bf, UnitMap *unit_map);
void add_action_to_queue(ActionQueue *queue, Action action, UnitMap *unit_map);
void print_action_queue(ActionQueue *queue);

#endif