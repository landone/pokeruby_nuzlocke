#ifndef GUARD_NUZLOCKE_H
#define GUARD_NUZLOCKE_H

#include "gba/types.h"
#include "constants/maps.h"

#define NUZ_MSG_CANT_CATCH 0

void nuzlocke_display_message(u8 taskId, u8 type);

bool8 nuzlocke_can_catch_mon_here();
void nuzlocke_set_mon_encounter_here();

bool8 nuzlocke_last_battler_fainted();
void nuzlocke_set_last_battler_fainted(bool8 val);

#endif // GUARD_NUZLOCKE_H