#include "sammi.h"
#include <thread>
#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

using namespace std;

std::wstring convertToWide2(const std::string_view &str)
{
    if (str.empty())
    {
        return std::wstring();
    }
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// constants and shared things
shared_ptr<SAMMI> sammi;

/**
 * Initializes the local SAMMI object and fires the first roundStartEvent
 */
void SAMMI_init()
{
    sammi = make_shared<SAMMI>();
    sammi->roundStart();
}

size_t findStringLength(char string[])
{
    int i = 0;
    while (string[i])
        i++;
    return i;
}

size_t findStringLength(const char string[])
{
    int i = 0;
    while (string[i])
        i++;
    return i;
}

/**
 * Parses the GameState data into types we can use, then gives it to the sammi object
 */
void SAMMI_update(AREDGameState_Battle *GameState)
{
    // level 1 data
    auto asEngine = GameState->get_0xBB8();
    // auto asEvents = GameState->get_0xBD8();

    // level 2 data
    auto player1block = asEngine->get_0x0(0); // there are only 2 entries in the array so this is fine
    auto player2block = asEngine->get_0x0(1);
    // auto pawn1 = asEngine->get_0x1498(0); // idk what these are used for, but they might be relevant to projectiles and such
    // auto pawn2 = asEngine->get_0x1498(1);
    // auto pawn3 = asEngine->get_0x1498(2);
    // auto pawn4 = asEngine->get_0x1498(3);
    // auto pawn5 = asEngine->get_0x1498(4);
    // auto pawn6 = asEngine->get_0x1498(5);
    // auto pawn7 = asEngine->get_0x1498(6);
    // auto event1 = asEvents->get_0x8(0); // seemingly used for events like reset, battle start, etc
    // auto event2 = asEvents->get_0x8(1); // should probably parse for round end and the like
    // auto event3 = asEvents->get_0x8(2);
    // auto event4 = asEvents->get_0x8(3);
    // auto event5 = asEvents->get_0x8(4);
    // auto event6 = asEvents->get_0x8(5);
    // auto event7 = asEvents->get_0x8(6);
    // auto event8 = asEvents->get_0x8(7);
    // auto event9 = asEvents->get_0x8(8);
    // auto event10 = asEvents->get_0x8(9);

    // level 3 data
    auto p1afro = player1block.entity->afro; // this is the better way to get data, block has all of the things entity has and more
    auto p1air = player1block.entity->airborne;
    // auto p1apd = player1block.entity->atk_param_defend; // there are extensions to these
    // auto p1apexc = player1block.entity->atk_param_ex_counter;
    // auto p1apexd = player1block.entity->atk_param_ex_defend;
    // auto p1apexn = player1block.entity->atk_param_ex_normal;
    auto p1aph = player1block.entity->atk_param_hit;
    auto p1blockamnt = player1block.entity->blockstun;
    auto p1cinectr = player1block.entity->cinematic_counter;
    auto p1ctr = player1block.entity->counterhit;
    auto p1spritename = player1block.entity->get_sprite_name();
    auto p1bbstate = player1block.entity->get_BB_state();
    auto p1hitstopamnt = player1block.entity->hitstop;
    auto p1hitstunamnt = player1block.entity->hitstun;
    auto p1blockstun = player1block.entity->is_in_blockstun();
    auto p1knockdown = player1block.entity->is_knockdown();
    auto p1hitstun = player1block.entity->is_in_hitstun();
    auto p1throwinv = player1block.entity->is_throw_invuln();
    auto p1strikeinv = player1block.entity->is_strike_invuln();
    auto p1hitting = player1block.entity->landed_hit;
    auto p1posx = player1block.entity->get_pos_x();
    auto p1posy = player1block.entity->get_pos_y();
    auto p1slowdown = player1block.entity->slowdown_timer;
    auto p1wakingup = player1block.entity->wakeup;

    // auto pw1name = pawn1->GetFullName();
    // auto pw2name = pawn2->GetFullName();
    // auto pw3name = pawn3->GetFullName();
    // auto pw4name = pawn4->GetFullName();
    // auto pw5name = pawn5->GetFullName();
    // auto pw6name = pawn6->GetFullName();
    // auto pw7name = pawn7->GetFullName();
    // auto e1type = event1.type;
    // auto e2type = event2.type;
    // auto e3type = event3.type;
    // auto e4type = event4.type;
    // auto e5type = event5.type;
    // auto e6type = event6.type;
    // auto e7type = event7.type;
    // auto e8type = event8.type;
    // auto e9type = event9.type;
    // auto e10type = event10.type;

    // level 4 data (atk_* stuff here)
    // auto p1datklvl = p1apd.atk_level;
    // auto p1datklvlcl = p1apd.atk_level_clash;
    // auto p1datklvlgr = p1apd.atk_level_guard;
    // auto p1datktyp = p1apd.atk_type;
    // auto p1dchipdmg = p1apd.chip_damage;
    // auto p1dchpdrate = p1apd.chip_damage_rate;
    // auto p1dmg = p1apd.damage;
    // auto p1dhstop = p1apd.hitstop;
    // auto p1dprorate = p1apd.proration;
    // auto p1dproratf = p1apd.proration_first;
    // auto p1dprorato = p1apd.proration_once;
    // auto p1dproratrf = p1apd.proration_rate_first;
    // auto p1dproratro = p1apd.proration_rate_once;
    // auto p1drisc = p1apd.risc;

    // auto p1hatklvl = p1aph.atk_level;
    // auto p1hatklvlcl = p1aph.atk_level_clash;
    // auto p1hatklvlgr = p1aph.atk_level_guard;
    auto p1hatktyp = p1aph.get_0x0();
    auto p1hchipdmg = p1aph.get_0x270();
    auto p1hchpdrate = p1aph.get_0x274();
    auto p1hdmg = p1aph.get_0xC();
    // auto p1hhstop = p1aph.hitstop;
    // auto p1hprorate = p1aph.proration;
    // auto p1hproratf = p1aph.proration_first;
    // auto p1hprorato = p1aph.proration_once;
    // auto p1hproratrf = p1aph.proration_rate_first;
    // auto p1hproratro = p1aph.proration_rate_once;
    auto p1hrisc = p1aph.get_0x258();
    auto p1hstagger = p1aph.get_0x14C();
    auto p1hunburst = p1aph.get_0x278();

    // auto p1enhitstun = p1apexn.atk_hitstun;
    // auto p1enuntech = p1apexn.atk_untech;
    // auto p1enwallstick = p1apexn.atk_wallstick_time;

    // auto p1edhitstun = p1apexd.atk_hitstun;
    // auto p1eduntech = p1apexd.atk_untech;
    // auto p1edwallstick = p1apexd.atk_wallstick_time;

    // auto p1echitstun = p1apexc.atk_hitstun;
    // auto p1ecuntech = p1apexc.atk_untech;
    // auto p1ecwallstick = p1apexc.atk_wallstick_time;

    // i wonder why i do this to myself....
    Output::send<LogLevel::Verbose>(STR("p1afro: {}\n"), p1afro);
    Output::send<LogLevel::Verbose>(STR("p1air: {}\n"), p1air);
    Output::send<LogLevel::Verbose>(STR("p1blockamnt: {}\n"), p1blockamnt);
    Output::send<LogLevel::Verbose>(STR("p1cinectr: {}\n"), p1cinectr);
    Output::send<LogLevel::Verbose>(STR("p1ctr: {}\n"), p1ctr);
    //auto sprnlen = findStringLength(p1spritename);
    Output::send<LogLevel::Verbose>(STR("p1spritename: {}\n"), convertToWide2(p1spritename));
    //auto bbstlen = findStringLength(p1bbstate);
    Output::send<LogLevel::Verbose>(STR("p1bbstate: {}\n"), convertToWide2(p1bbstate));
    Output::send<LogLevel::Verbose>(STR("p1hitstopamnt: {}\n"), p1hitstopamnt);
    Output::send<LogLevel::Verbose>(STR("p1hitstunamnt: {}\n"), p1hitstunamnt);
    Output::send<LogLevel::Verbose>(STR("p1blockstun: {}\n"), p1blockstun);
    Output::send<LogLevel::Verbose>(STR("p1knockdown: {}\n"), p1knockdown);
    Output::send<LogLevel::Verbose>(STR("p1hitstun: {}\n"), p1hitstun);
    Output::send<LogLevel::Verbose>(STR("p1throwinv: {}\n"), p1throwinv);
    Output::send<LogLevel::Verbose>(STR("p1strikeinv: {}\n"), p1strikeinv);
    Output::send<LogLevel::Verbose>(STR("p1hitting: {}\n"), p1hitting);
    Output::send<LogLevel::Verbose>(STR("p1posx: {}\n"), p1posx);
    Output::send<LogLevel::Verbose>(STR("p1posy: {}\n"), p1posy);
    Output::send<LogLevel::Verbose>(STR("p1slowdown: {}\n"), p1slowdown);
    Output::send<LogLevel::Verbose>(STR("p1wakingup: {}\n"), p1wakingup);
    // Output::send<LogLevel::Verbose>(STR("pw1name: {}\n"), pw1name);
    // Output::send<LogLevel::Verbose>(STR("pw2name: {}\n"), pw2name);
    // Output::send<LogLevel::Verbose>(STR("pw3name: {}\n"), pw3name);
    // Output::send<LogLevel::Verbose>(STR("pw4name: {}\n"), pw4name);
    // Output::send<LogLevel::Verbose>(STR("pw5name: {}\n"), pw5name);
    // Output::send<LogLevel::Verbose>(STR("pw6name: {}\n"), pw6name);
    // Output::send<LogLevel::Verbose>(STR("pw7name: {}\n"), pw7name);
    // Output::send<LogLevel::Verbose>(STR("e1type: {}\n"), e1type);
    // Output::send<LogLevel::Verbose>(STR("e1type: {}\n"), e1type);
    // Output::send<LogLevel::Verbose>(STR("e3type: {}\n"), e3type);
    // Output::send<LogLevel::Verbose>(STR("e4type: {}\n"), e4type);
    // Output::send<LogLevel::Verbose>(STR("e5type: {}\n"), e5type);
    // Output::send<LogLevel::Verbose>(STR("e6type: {}\n"), e6type);
    // Output::send<LogLevel::Verbose>(STR("e7type: {}\n"), e7type);
    // Output::send<LogLevel::Verbose>(STR("e8type: {}\n"), e8type);
    // Output::send<LogLevel::Verbose>(STR("e9type: {}\n"), e9type);
    // Output::send<LogLevel::Verbose>(STR("e10type: {}\n"), e10type);
    // Output::send<LogLevel::Verbose>(STR("p1datklvl: {}\n"), p1datklvl);
    // Output::send<LogLevel::Verbose>(STR("p1datklvlcl: {}\n"), p1datklvlcl);
    // Output::send<LogLevel::Verbose>(STR("p1datklvlgr: {}\n"), p1datklvlgr);
    // Output::send<LogLevel::Verbose>(STR("p1datktyp: {}\n"), p1datktyp);
    // Output::send<LogLevel::Verbose>(STR("p1dchipdmg: {}\n"), p1dchipdmg);
    // Output::send<LogLevel::Verbose>(STR("p1dchpdrate: {}\n"), p1dchpdrate);
    // Output::send<LogLevel::Verbose>(STR("p1dmg: {}\n"), p1dmg);
    // Output::send<LogLevel::Verbose>(STR("p1dhstop: {}\n"), p1dhstop);
    // Output::send<LogLevel::Verbose>(STR("p1dprorate: {}\n"), p1dprorate);
    // Output::send<LogLevel::Verbose>(STR("p1dproratf: {}\n"), p1dproratf);
    // Output::send<LogLevel::Verbose>(STR("p1dprorato: {}\n"), p1dprorato);
    // Output::send<LogLevel::Verbose>(STR("p1dproratrf: {}\n"), p1dproratrf);
    // Output::send<LogLevel::Verbose>(STR("p1dproratro: {}\n"), p1dproratro);
    // Output::send<LogLevel::Verbose>(STR("p1drisc: {}\n"), p1drisc);
    // Output::send<LogLevel::Verbose>(STR("p1hatklvl: {}\n"), p1hatklvl);
    // Output::send<LogLevel::Verbose>(STR("p1hatklvlcl: {}\n"), p1hatklvlcl);
    // Output::send<LogLevel::Verbose>(STR("p1hatklvlgr: {}\n"), p1hatklvlgr);
    Output::send<LogLevel::Verbose>(STR("p1hatktyp: {}\n"), p1hatktyp);
    Output::send<LogLevel::Verbose>(STR("p1hchipdmg: {}\n"), p1hchipdmg);
    Output::send<LogLevel::Verbose>(STR("p1hchpdrate: {}\n"), p1hchpdrate);
    Output::send<LogLevel::Verbose>(STR("p1hdmg: {}\n"), p1hdmg);
    // Output::send<LogLevel::Verbose>(STR("p1hhstop: {}\n"), p1hhstop);
    // Output::send<LogLevel::Verbose>(STR("p1hprorate: {}\n"), p1hprorate);
    // Output::send<LogLevel::Verbose>(STR("p1hproratf: {}\n"), p1hproratf);
    // Output::send<LogLevel::Verbose>(STR("p1hprorato: {}\n"), p1hprorato);
    // Output::send<LogLevel::Verbose>(STR("p1hproratrf: {}\n"), p1hproratrf);
    // Output::send<LogLevel::Verbose>(STR("p1hproratro: {}\n"), p1hproratro);
    Output::send<LogLevel::Verbose>(STR("p1hrisc: {}\n"), p1hrisc);
    Output::send<LogLevel::Verbose>(STR("p1hstagger: {}\n"), p1hstagger);
    Output::send<LogLevel::Verbose>(STR("p1hunburst: {}\n"), p1hunburst);
    // Output::send<LogLevel::Verbose>(STR("p1enhitstun: {}\n"), p1enhitstun);
    // Output::send<LogLevel::Verbose>(STR("p1enuntech: {}\n"), p1enuntech);
    // Output::send<LogLevel::Verbose>(STR("p1enwallstick: {}\n"), p1enwallstick);
    // Output::send<LogLevel::Verbose>(STR("p1edhitstun: {}\n"), p1edhitstun);
    // Output::send<LogLevel::Verbose>(STR("p1eduntech: {}\n"), p1eduntech);
    // Output::send<LogLevel::Verbose>(STR("p1edwallstick: {}\n"), p1edwallstick);
    // Output::send<LogLevel::Verbose>(STR("p1echitstun: {}\n"), p1echitstun);
    // Output::send<LogLevel::Verbose>(STR("p1ecuntech: {}\n"), p1ecuntech);
    // Output::send<LogLevel::Verbose>(STR("p1ecwallstick: {}\n"), p1ecwallstick);

    /// player 2 yaaay...
    //<>

    // todo: implement
    // sammi->stateUpdate();
}

/**
 * Fires the roundEnd before deleting the object
 */
void SAMMI_kill()
{
    sammi->roundEnd(Player1Win, Death); // todo: put in real values or make the sammi object figure them out
    sammi.reset();
}

void SAMMI::roundStart()
{
    // TODO: send data. use thread or other func??
}

/**
 * Also sends currentFrame
 */
void SAMMI::stateUpdate(uint32_t roundTimeLimit, uint32_t roundTimeLeft, PlayerState &player1, PlayerState &player2)
{
    p1prev = p1;
    p2prev = p2;
    p1 = player1;
    p2 = player2;
    currentFrame++; // should be called every frame
    // TODO: other stuff, send data
}

/**
 * Also sends currentFrame, attackerState, victimState, and victimPreviousState
 */
void SAMMI::hitEvent(HitType hitType, bool wasBlocked, uint8_t attackLevel, uint16_t damage, ObjectID attacker, ObjectID victim, uint16_t comboLength)
{
}

/**
 * Also sends currentFrame, player1State and player2State
 */
void SAMMI::objectCreated(wstring objectName, ObjectID creator)
{
}

/**
 * Also sends currentFrame
 */
void SAMMI::roundEnd(Winner winner, RoundEndCause cause)
{
}

/**
 * Also sends currentFrame, victimState and victimPreviousState
 */
void SAMMI::comboEnd(uint16_t combo_length, uint16_t damage, ObjectID victim)
{
}

wstring SAMMI::getP1State()
{
    return p1.state;
}

wstring SAMMI::getP2State()
{
    return p2.state;
}