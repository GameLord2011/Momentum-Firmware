#include "t5577_config.h"

const t5577_modulation all_mods[] = {
    {"Direct", LFRFID_T5577_MODULATION_DIRECT},
    {"PSK1", LFRFID_T5577_MODULATION_PSK1},
    {"PSK2", LFRFID_T5577_MODULATION_PSK2},
    {"PSK3", LFRFID_T5577_MODULATION_PSK3},
    {"FSK1", LFRFID_T5577_MODULATION_FSK1},
    {"FSK2", LFRFID_T5577_MODULATION_FSK2},
    {"FSK1a", LFRFID_T5577_MODULATION_FSK1a},
    {"FSK2a", LFRFID_T5577_MODULATION_FSK2a},
    {"ASK/MC", LFRFID_T5577_MODULATION_MANCHESTER},
    {"Biphase", LFRFID_T5577_MODULATION_BIPHASE},
    {"Diphase", LFRFID_T5577_MODULATION_DIPHASE},
};

const t5577_rf_clock all_rf_clocks[] = {
    {8, LFRFID_T5577_BITRATE_RF_8},
    {16, LFRFID_T5577_BITRATE_RF_16},
    {32, LFRFID_T5577_BITRATE_RF_32},
    {40, LFRFID_T5577_BITRATE_RF_40},
    {50, LFRFID_T5577_BITRATE_RF_50},
    {64, LFRFID_T5577_BITRATE_RF_64},
    {100, LFRFID_T5577_BITRATE_RF_100},
    {128, LFRFID_T5577_BITRATE_RF_128}};