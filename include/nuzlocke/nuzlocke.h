#ifndef GUARD_NUZLOCKE_H
#define GUARD_NUZLOCKE_H

#include "gba/types.h"
#include "constants/maps.h"

#define NUZ_MSG_CANT_CATCH 0

bool8 nuzlocke_can_catch_mon_here();
void nuzlocke_display_message(u8 taskId, u8 type);

void nuzlocke_set_mon_encounter_here();

#endif // GUARD_NUZLOCKE_H