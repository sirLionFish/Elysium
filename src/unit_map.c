#include "include/global_limit.h"
#include "include/unit_struct.h"
#include "include/unit_map.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

unsigned int hash(const char *str) {
  unsigned int hash_val = 5381;
  int c;
  while ((c = *str++))
    hash_val = ((hash_val << 5) + hash_val) + c;
  return hash_val % HASH_MAP_SIZE;
}

void insert_unit(UnitMap *unit_map, Unit *unit) {
  unsigned int index = hash(unit->uid);

  UnitMapEntry *new_entry = (UnitMapEntry *)malloc(sizeof(UnitMapEntry));
  if (!new_entry) {
    printf("Memory allocation failed for UnitMap entry for unit %s\n", unit->uid);
    return;
  }

  //copy the unit's uid into te new entry
  strncpy(new_entry->uid, unit->uid, sizeof(new_entry->uid) - 1);
  new_entry->uid[sizeof(new_entry->uid) - 1] = '\0';

  new_entry->unit = unit;

  new_entry->next = unit_map->table[index];
  unit_map->table[index] = new_entry;
}

Unit *get_unit_by_uid(UnitMap *unit_map, const char *uid) {
  unsigned int index = hash(uid);

  //traverse the linked list at bucket
  UnitMapEntry *entry = unit_map->table[index];
  while (entry != NULL) {
    if (strcmp(entry->uid, uid) == 0) {
      return entry->unit;
    }
    entry = entry->next;
  }
  return NULL;
}

void print_unit_map(UnitMap *unit_map) {
  printf("--- UnitMap Contents ----\n");
  for (int i = 0; i < HASH_MAP_SIZE; i++) {
    UnitMapEntry *entry = unit_map->table[i];
    if (entry) {
      printf("Bucket %d:\n", i);
      while (entry != NULL) {
        printf(" UID: %s | Unit Name: %s | Unit ID: %d\n",
          entry->uid,
          entry->unit->name,
          entry->unit->unit_id);
        entry = entry->next;
      }
    }
  }
  printf("---- End of UnitMap ---\n");
}
