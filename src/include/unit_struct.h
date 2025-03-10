#ifndef UNIT_STRUCT_H
#define UNIT_STRUCT_H

#include "global_limit.h"
#include "stats.h"

 typedef struct {
    int unit_id;
    char uid[MAX_UID_LENGTH];
    char name[50];
    int position_row;
    int position_col;
    int allegience;
    int action_point;
    Stats stats;
    int skill_list[MAX_UNIT_SKILLS];
  } Unit;

#endif