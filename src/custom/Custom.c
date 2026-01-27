#include "custom/Custom.h"

#include "gba/types.h"
#include "global.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "event_data.h"
#include "pokedex.h"
#include "overworld.h"
#include "constants/maps.h"
#include "main.h"

void SetFlags() {

    u16 tempFlag;

    EnableNationalPokedex();
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_SYS_POKENAV_GET);
    FlagSet(FLAG_CUSTOM_DEBUG_MODE);

    //Give all badges
    for (tempFlag = FLAG_BADGE01_GET; tempFlag <= FLAG_BADGE08_GET; tempFlag++)
        FlagSet(tempFlag);

    //Give all town visit flags
    for (tempFlag = FLAG_VISITED_LITTLEROOT_TOWN; tempFlag <= FLAG_VISITED_EVER_GRANDE_CITY; tempFlag++)
        FlagSet(tempFlag);
    
}

void GiveFly(struct Pokemon* mon) { SetMonMoveSlot(mon, MOVE_FLY, 0); }
void GiveWaterHMs(struct Pokemon* mon) {
    SetMonMoveSlot(mon, MOVE_SURF, 0);
    SetMonMoveSlot(mon, MOVE_WATERFALL, 1);
    SetMonMoveSlot(mon, MOVE_DIVE, 2);
}
void GiveFlash(struct Pokemon* mon) { SetMonMoveSlot(mon, MOVE_FLASH, 0); }
void GivePhysicalHMs(struct Pokemon* mon) {
    SetMonMoveSlot(mon, MOVE_CUT, 0);
    SetMonMoveSlot(mon, MOVE_ROCK_SMASH, 1);
    SetMonMoveSlot(mon, MOVE_STRENGTH, 2);
}

void OnNewGame() {

    const char* playerName = "Wan!";
    SetFlags();
    FormatAscii(playerName, gSaveBlock2.playerName, 7);
    GiveMon(SPECIES_ZAPDOS, 60, GiveFly);
    GiveMon(SPECIES_ARTICUNO, 60, GiveWaterHMs);
    GiveMon(SPECIES_MOLTRES, 60, GiveFlash);
    GiveMon(SPECIES_LUGIA, 60, GivePhysicalHMs);

    /*Overworld_SetWarpDestination(MAP_GROUP(MAP_ABANDONED_SHIP_CAPTAINS_OFFICE), MAP_NUM(MAP_ABANDONED_SHIP_CAPTAINS_OFFICE), -1, -1, -1);
    WarpIntoMap();
    do_load_map_stuff_loop(&gMain.state);*/
    

}

void GiveMon(u16 species, u8 level, void(*MonConstructor)(struct Pokemon*)) {

    struct Pokemon mon;

    CreateMon(&mon, species, level, 32, 0, 0, 0, 0);
    if (MonConstructor != NULL) {
        MonConstructor(&mon);
    }
    GiveMonToPlayer(&mon);

    AddToPokedex(species);

}

void AddToPokedex(u16 species) {

    u16 nationalDexNum = SpeciesToNationalPokedexNum(species);
    GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
    GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);

}

void FormatAscii(char* string, u8* destination, int maxLength) {
    int i = 0;
    while (string[i] != '\0' && i < maxLength) {
        char c = string[i];
        u8 newVal = 0;
        if (c >= 'A' && c <= 'Z') {
            newVal = 0xBB + (c - 'A');
        }
        else if (c >= 'a' && c <= 'z') {
            newVal = 0xD5 + (c - 'a');
        }
        else if (c >= '0' && c <= '9') {
            newVal = 0xA1 + (c - '0');
        }
        else {
            switch (c) {
                case '!':
                    newVal = 0xAB;
                    break;
                case '?':
                    newVal = 0xAC;
                    break;
                case '.':
                    newVal = 0xAD;
                    break;
                case ',':
                    newVal = 0xB8;
                    break;
                case '-':
                    newVal = 0xAE;
                    break;
                case '/':
                    newVal = 0xBA;
                    break;
            }
        }
        destination[i] = newVal;
        i++;
    }
    destination[i] = 0xFF; // End of string
}