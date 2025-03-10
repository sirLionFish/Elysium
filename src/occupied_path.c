#include "include/occupied_path.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

unsigned int hash_position(int row, int col) {
  return (row * 31 + col) % HASH_MAP_SIZE;
}

void insert_occupied_path(OccupiedPathMap *occupied_path, const char *actor_uid, int dest_row, int dest_col) {
  unsigned int index = hash_position(dest_row, dest_col);

  OccupiedPathEntry *new_entry = (OccupiedPathEntry *)malloc(sizeof(OccupiedPathEntry));
  if (!new_entry) {
    printf("Memory allocation failed for OccupiedPathEntry\n");
    return;
  }

  strncpy(new_entry->actor_uid, actor_uid, sizeof(new_entry->actor_uid) - 1);
  new_entry->actor_uid[sizeof(new_entry->actor_uid) - 1] = '\0';
  new_entry->dest_row = dest_row;
  new_entry->dest_col = dest_col;
  new_entry->next = occupied_path->table[index];
  occupied_path->table[index] = new_entry;
}

void detect_collisions(OccupiedPathMap *occupied_path) {
  printf("Detecting Collisions..\n");
  for (int i = 0; i < HASH_MAP_SIZE; i++) {
    OccupiedPathEntry *entry = occupied_path->table[i];
    while (entry && entry->next) {
      OccupiedPathEntry *current = entry->next;
      while (current) {
        if (entry->dest_row == current->dest_row && entry->dest_col == current->dest_col) {
          printf("Collision detected between %s and %s at (%d, %d)\n", entry->actor_uid, current->actor_uid, entry->dest_row, entry->dest_col);
        }
        current = current->next;
      }
      entry = entry->next;
    }
  }
}

void clear_occupied_path(OccupiedPathMap *occupied_path) {
  for (int i = 0; i < HASH_MAP_SIZE; i++) {
    OccupiedPathEntry *entry = occupied_path->table[i];
    while (entry) {
      OccupiedPathEntry *temp = entry;
      entry = entry->next;
      free(temp);
    }
    occupied_path->table[i] = NULL;
  }
}