#ifndef UNIT_MAP_H
#define UNIT_MAP_H

#include "global_limit.h"
#include "unit_struct.h"

typedef struct UnitMapEntry {
  char uid[50];
  Unit *unit;
  struct UnitMapEntry *next;
} UnitMapEntry;

typedef struct  {
  UnitMapEntry *table[HASH_MAP_SIZE];
} UnitMap;

void insert_unit_to_unit_map(UnitMap *unit_map, Unit *unit);
void print_unit_map(UnitMap *unit_map);
Unit *get_unit_by_uid(UnitMap *unit_map, const char *uid);

#endif