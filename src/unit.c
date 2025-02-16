#include "include/unit.h"
#include "include/global_limit.h"
#include "include/army.h"
#include "include/skill.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int global_unit_pool_count = 0;

Unit *create_and_add_unit(const char *name, int health, int attack, int defence, int range, int travel_speed) {
    if (global_unit_pool_count >= MAX_UNIT_POOL) {
        printf("Global unit pool is full!\n");
        return NULL;
    }

    Unit *unit = (Unit *)malloc(sizeof(Unit));
    if (!unit) {
        printf("Memory allocation failed for unit %s.\n", name);
        return NULL;
    }

    unit->unit_id = global_unit_pool_count;
    strncpy(unit->name, name, sizeof(unit->name) - 1);
    unit->name[sizeof(unit->name) - 1] = '\0';
    unit->position_row = -1;
    unit->position_col = -1;
    unit->allegiance = 0;
    unit->stats.health = health;
    unit->stats.max_health = health;
    unit->stats.attack = attack;
    unit->stats.defence = defence;
    unit->stats.range = range;
    unit->stats.travel_speed = travel_speed;

    global_unit_pool[global_unit_pool_count++] = unit;
    return unit;
}