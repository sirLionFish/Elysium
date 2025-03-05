#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

  #include "battlefield_struct.h"
  #include "unit_map.h"

  void initialize_battlefield(Battlefield *battlefield);
  void add_faction_to_battlefield(Battlefield *bf, int faction_id, int faction_index, UnitMap *unit_map);
  void display_battlefield(const Battlefield* battlefield);
  
#endif