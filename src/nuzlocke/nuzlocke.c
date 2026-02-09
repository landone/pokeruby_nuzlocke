#include "nuzlocke/nuzlocke.h"

#include "global.h"
#include "menu.h"
#include "menu_helpers.h"
#include "string_util.h"

#include "custom/Custom.h"

static bool8 caught_map[MAP_GROUPS_COUNT][128/8];
extern void CleanUpItemMenuMessage(u8 taskId);

const u8 cant_catch_str[] = _("Can not use this here.\nIt's not the first Pokémon encounter\nin this area!");

void nuzlocke_display_message(u8 taskId, u8 type) {

    u8* str_pos;
    gStringVar4[0] = EOS;

    switch (type) {
        case NUZ_MSG_CANT_CATCH:
            str_pos = StringCopy(gStringVar4, cant_catch_str);
            *(str_pos++) = CHAR_PROMPT_CLEAR;
            *str_pos = EOS;
            Menu_EraseWindowRect(0, 13, 13, 20);
            DisplayItemMessageOnField(taskId, gStringVar4, CleanUpItemMenuMessage, 1);
            break;
    }

}

bool8 nuzlocke_can_catch_mon_here() {

    s8 map_group = gSaveBlock1.location.mapGroup;
    s8 map_num = gSaveBlock1.location.mapNum;
    s8 map_num_index = map_num / 8;
    s8 map_num_bit = map_num % 8;

    return (caught_map[map_group][map_num_index] & (1 << map_num_bit)) == 0;

}

void nuzlocke_set_mon_encounter_here() {

    s8 map_group = gSaveBlock1.location.mapGroup;
    s8 map_num = gSaveBlock1.location.mapNum;
    s8 map_num_index = map_num / 8;
    s8 map_num_bit = map_num % 8;
    caught_map[map_group][map_num_index] |= (1 << map_num_bit);

}