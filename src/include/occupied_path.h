#ifndef OCCUPIED_PATH_H
#define OCCUPIED_PATH_H

#include "global_limit.h"

typedef struct OccupiedPathEntry {
  char actor_uid[MAX_UID_LENGTH];
  int dest_row;
  int dest_col;
  struct OccupiedPathEntry *next;
} OccupiedPathEntry;

typedef struct {
  OccupiedPathEntry *table[HASH_MAP_SIZE];
} OccupiedPathMap;

void insert_occupied_path(OccupiedPathMap *occupied_path, const char *actor_uid, int dest_row, int dest_col);
void detect_collisions(OccupiedPathMap *occupied_path);

#endif