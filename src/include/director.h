#ifndef DIRECTOR_H
#define DIRECTOR_H

  #include "battlefield.h"
  #include "unit_struct.h"
  #include "unit_map.h"
  
  typedef enum {
    TARGET_IN_SKILL_RANGE,
    NO_TARGET_IN_SKILL_RANGE
  } TargetStatus;

  typedef struct {
    const char *target_uid;
    int distance;
    TargetStatus target_status;
  } TargetResult;

  TargetResult director_calculate(Unit *actor, UnitMap *unit_map);

#endif