// #ifndef ACTION_H
// #define ACTION_H

// #include "unit.h"
// #include "skill.h"
// #include "battlefield.h"

//   typedef enum {
//     RANGE,
//     PHYSICAL,
//     MAGICAL,
//     DEVINE,
//     HELLISH
//   } ActionType;

//   typedef enum {
//     TARGET_SELF,
//     TARGET_ALLY,
//     TARGET_ENEMY,
//     TARGET_EVERYONE
//   } TargetType;

//   typedef struct {
//     TargetType target;
//     int min_effect;
//     int max_effect;
//     int hit_chance;
//     int critical_chance;
//     int range;
//     int duration;
//     int effect_value;
//     int aoe;
//   } Action;

//   int validate_target(Unit *actor, Unit *target, Skill *skill);
//   void apply_action_to_unit(Unit *target, Skill *skill);
//   void execute_action(Battlefield *battlefield, Unit *actor, int skill_id, int target_row, int target_col);

// #endif