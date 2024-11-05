#include "sammi.h"

// sammi stuff

void SAMMI_start(AREDGameState_Battle *GameState) {
    Output::send<LogLevel::Verbose>(STR("SAMMI init func: entity count is: {}\n"), GameState->get_0xBB8()->entity_count);
    //Output::send<LogLevel::Verbose>(STR("SAMMI init func: entity 0's bbs_file is: {}\n"), GameState->get_0xBB8()->get_0xC10(0)->bbs_file);
    //Output::send<LogLevel::Verbose>(STR("SAMMI init func: player_block 0 is: {}\n"), GameState->get_0xBB8()->get_0x0(0).);
}