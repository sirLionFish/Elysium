#ifndef FACTION_CARD_H
#define FACTION_CARD_H

#define ROW_MAX 8
#define COL_MAX 10
#define MAX_SKILLS 100
#define MAX_UNIT_SKILLS 10
#define GLOBAL_UNIT_POOL_SIZE 100

  typedef enum {
    Class_MELEE,
    Class_RANGE,
    Class_MAGIC,
    Class_MAX
  } ClassType;

  typedef enum {
    ALLEGIANCE_PLAYER,
    ALLEGIANCE_ENEMY
  } Allegiance;

  typedef enum {
    RANGE,
    PHYSICAL,
    MAGICAL,
    DEVINE,
    HELLISH
  } ActionType;

  typedef enum {
    RANGE_CLASS,
    MELEE,
    DEFENSE,
    RANGE_MELEE,
    MELEE_DEFENSE,
    RANGE_DEFENCE,
    RANGE_MELEE_DEFENCE
  } Class;

  typedef enum {
    TARGET_SELF,
    TARGET_ALLY,
    TARGET_ENEMY,
    TARGET_EVERYONE
  } TargetType;

  typedef struct {
    TargetType target;
    int min_effect;
    int max_effect;
    int hit_chance;
    int critical_chance;
    int range;
    int duration;
    int effect_value;
    int aoe;
  } Action;

  typedef struct {
    int health;
    int max_health;
    int attack;
    int defence;
    int range;
    int travel_speed;
  } Stats;

  typedef struct {
    int id;
    char name[20];
    Action action;
    Stats stat_change;
  } Skill;

  typedef struct {
    int unit_id;
    char name[50];
    int position_row;
    int position_col;
    Allegiance allegiance;
    Stats stats;
    Skill skills;
  } Unit;

  typedef struct {
    Unit units[COL_MAX];
    int unit_count;
    int row_formation_id;
  } RowFormation;

  typedef struct {
    int army_id;
    RowFormation rows[ROW_MAX];
  } Army;

  typedef struct {
    int faction_id;
    Army army;
    char name[50];
  } Faction;

  typedef struct {
    Unit *grid[ROW_MAX][COL_MAX];
    Faction factions[2];
    int global_turn;
  } Battlefield;

  Unit global_unit_pool[GLOBAL_UNIT_POOL_SIZE];
  
  Unit create_unit(const char *name, int health, int attack, int defence, int range, int travel_speed);
  Skill create_skill(const char *name, int health, int attack, int defence, int range, int travel_speed);
  void initialize_army(Army *army, int army_id);
  int add_unit_to_army(Army *army, Unit unit, int row_formation_id);

  void display_faction(const Faction *faction);
  int check_victory_condition(const Army *army);

  int is_target_in_range(const Unit *unit, const Army *Army);

  // void process_faction_turn(Battlefield *battlefield);

  // // int add_unit_to_army(Army *army, Unit unit, int row, int col);
  // void add_army_to_row(Army *army, ClassType, Unit unit); //check this out again

  int move_unit_column(Army *army, int row, int from_col, int to_col);
  int move_unit_row(Army *army, int from_row, int from_col, int to_row, int to_col);
  int move_unit(Battlefield *battlefield, int src_row, int src_col, int dest_row, int dest_col);

  void display_battlefield(const Battlefield* battlefield);
  void initialize_battlefield(Battlefield *battlefield);
  int place_unit_on_battlefield(Battlefield *battlefield, Unit *unit, int row, int col);

  void execute_action(Battlefield *battlefield, Unit *actor, int skill_id, int target_row, int target_col);

  int validate_target(Unit *actor, Unit *target, Skill *skill);
  Skill* get_skill_by_id(int skill_id);
  void apply_action_to_unit(Unit *target, Skill *skill);

  Skill skill_registry[MAX_SKILLS];

#endif