#ifndef DIRECTOR_H
#define DIRECTOR_H

  #include "battlefield.h"
  #include "unit_struct.h"

  Unit *find_nearest_target(Battlefield *bf, Unit *actor);
  void director_calculate(Battlefield *bf);

#endif