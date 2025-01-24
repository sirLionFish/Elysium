#ifndef FACTION_CARD_H
#define FACTION_CARD_H

  typedef enum {
    ROW_MELEE,
    ROW_RANGED,
    ROW_MAGIC,
    ROW_MAX
  } RowType;

  typedef struct {
    char name[50];
    int health;
    int max_health;
    int attack;
    int defense;
    int range;
    int speed;
    int special_ability;
  } Unit;

  typedef struct {
    Unit units[10];
    int unit_count;
  } Row;

  typedef struct {
    Row rows[ROW_MAX];
    int total_score;
  } Army;

  typedef struct {
    Army army1;
    Army army2;
    int size;
  } Battlefield;

  Unit create_unit(const char *name, int health, int attack, int defense, int range, int speed, int special_ability);
  // Army create_army(int unit_count);
  // void destroy_army(Army *army);
  // void display_army(const Army *army);
  void add_unit_to_row(Army *army, RowType, Unit unit);
  int calculate_army_score(const Army *army);

#endif