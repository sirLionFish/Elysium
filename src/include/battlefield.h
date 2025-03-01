#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

  #include "battlefield_struct.h"

  void initialize_battlefield(Battlefield *battlefield);
  int add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index);
  void display_battlefield(const Battlefield* battlefield);
  
#endif