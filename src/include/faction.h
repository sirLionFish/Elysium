#ifndef FACTION_CARD_H
#define FACTION_CARD_H

#include "global_limit.h"
#include "army.h"

  typedef struct {
    int faction_id;
    Army army;
    char name[50];
  } Faction;

  Faction *global_faction_pool[MAX_FACTION_POOL];
  void initialize_faction(const char *name, int army_id);
  void display_faction(const Faction *faction);
  int global_faction_pool_count;
  
#endif