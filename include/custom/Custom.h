#ifndef GUARD_CUSTOM_H
#define GUARD_CUSTOM_H

#include "gba/types.h"
#include "global.h"

void OnNewGame();

void GiveMon(u16 species, u8 level, void(*MonConstructor)(struct Pokemon*));

void AddToPokedex(u16 species);

void FormatAscii(char* string, u8* destination, int maxLength);

#endif // GUARD_CUSTOM_H