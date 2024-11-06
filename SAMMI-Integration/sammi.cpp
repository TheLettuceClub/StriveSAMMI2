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
    // Output::send<LogLevel::Verbose>(STR("SAMMI init func: thread started, looping\n"));
    // Output::send<LogLevel::Verbose>(STR("SAMMI init func: entity count is: {}\n"), GameState->get_0xBB8()->entity_count);
    // Output::send<LogLevel::Verbose>(STR("SAMMI init func: entity 0's bbs_file is: {}\n"), convertToWide2(GameState->get_0xBB8()->get_0xC10(0)->bbs_file));
    // Output::send<LogLevel::Verbose>(STR("SAMMI init func: player_block 0's sprite duration is: {}\n"), GameState->get_0xBB8()->get_0x0(0).get_0x8()->sprite_duration);
    // Output::send<LogLevel::Verbose>(STR("SAMMI init func: player_block 0's sprite name is: {}\n"), convertToWide2(GameState->get_0xBB8()->get_0x0(0).get_0x8()->get_sprite_name()));

    // level 1 data
    auto asEngine = GameState->get_0xBB8();
    // auto asScene = GameState->get_0xBC0();
    // auto asEvents = GameState->get_0xBD8();

    // level 2 data
    // auto player1entity = asEngine->get_0xC10(0); //on roundstart, there are only two for sol v ky. may break for other chars????
    // auto player2entity = asEngine->get_0xC10(1);
    auto player1block = asEngine->get_0x0(0); // there are only 2 entries in the array so this is fine
    auto player2block = asEngine->get_0x0(1);
    // auto player1inputs = asEngine->get_0x37A8(0); //there are six here likely for TO3 support. assuming that the first two are non-TO3 p1/2
    // auto player2inputs = asEngine->get_0x37A8(1);
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
    // player1block.entity->act_reg_0;
    // auto p1skillid = player1block.entity->action_info.skill_id;
    // auto p1skillidreg = player1block.entity->action_info_reg.skill_id;
    // auto p1acttime = player1block.entity->action_time;
    // player1block.entity->activation_range_x_max;
    //  player1block.entity->activation_range_x_min;
    // player1block.entity->active;
    auto p1air = player1block.entity->airborne;
    auto p1apd = player1block.entity->atk_param_defend; // there are extensions to these
    auto p1apexc = player1block.entity->atk_param_ex_counter;
    auto p1apexd = player1block.entity->atk_param_ex_defend;
    auto p1apexn = player1block.entity->atk_param_ex_normal;
    auto p1aph = player1block.entity->atk_param_hit;
    /// player1block.entity->attached; //if this exists, attached. likely used for baiken tether
    // auto p1atkflg = player1block.entity->attack_flag;
    // auto p1bdinv = player1block.entity->backdash_invuln;
    // auto p1bbsfile = player1block.entity->bbs_file; // char *
    auto p1blockamnt = player1block.entity->blockstun;
    // auto p1canact = player1block.entity->can_act();
    // auto p1cangatling = player1block.entity->can_gatling_cancel();
    // auto p1canwhiff = player1block.entity->can_whiff_cancel();
    auto p1cinectr = player1block.entity->cinematic_counter;
    auto p1ctr = player1block.entity->counterhit;
    // auto p1cmnactid = player1block.entity->cur_cmn_action_id; // enums to an int
    // auto p1enflg = player1block.entity->enable_flag;
    // auto p1dir = player1block.entity->facing;                                  // enums to 0 for right and 1 for left
    // auto p1firstcmd = player1block.entity->first_script_cmd;                   // char *
    auto p1spritename = player1block.entity->get_sprite_name();                // const char *
    auto p1bbstate = player1block.entity->get_BB_state();                      // const char *
    // auto p1currmovename = player1block.entity->get_current_move()->get_name(); // const char *
    // auto p1grav = player1block.entity->gravity;
    // auto p1height = player1block.entity->ground_height;
    auto p1hitstopamnt = player1block.entity->hitstop;
    auto p1hitstunamnt = player1block.entity->hitstun;
    // auto p1active = player1block.entity->is_active();
    auto p1blockstun = player1block.entity->is_in_blockstun();
    auto p1knockdown = player1block.entity->is_knockdown();
    auto p1hitstun = player1block.entity->is_in_hitstun();
    // player1block.entity->is_move(); //query mechanism??
    auto p1throwinv = player1block.entity->is_throw_invuln();
    auto p1strikeinv = player1block.entity->is_strike_invuln();
    auto p1hitting = player1block.entity->landed_hit;
    // auto p1nextcmd = player1block.entity->next_script_cmd; // char *
    // auto p1index = player1block.entity->player_index;      // unsigned char
    auto p1posx = player1block.entity->get_pos_x();
    auto p1posy = player1block.entity->get_pos_y();
    // auto p1scriptbase = player1block.entity->script_base; // char *
    auto p1slowdown = player1block.entity->slowdown_timer;
    // auto p1thrwrng = player1block.entity->throw_range;
    // auto p1velx = player1block.entity->vel_x;
    // auto p1vely = player1block.entity->vel_y;
    auto p1wakingup = player1block.entity->wakeup;

    // auto p1name = pawn1->GetFullName();
    // auto p2name = pawn2->GetFullName();
    // auto p3name = pawn3->GetFullName();
    // auto p4name = pawn4->GetFullName();
    // auto p5name = pawn5->GetFullName();
    // auto p6name = pawn6->GetFullName();
    // auto p7name = pawn7->GetFullName();
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
    auto p1datklvl = p1apd.atk_level; // repeat for p1aph
    auto p1datklvlcl = p1apd.atk_level_clash;
    auto p1datklvlgr = p1apd.atk_level_guard;
    auto p1datktyp = p1apd.atk_type;
    auto p1dchipdmg = p1apd.chip_damage;
    auto p1dchpdrate = p1apd.chip_damage_rate;
    auto p1dmg = p1apd.damage;
    // auto p1dfdpush = p1apd.fd_min_pushback;
    // auto p1dgrab = p1apd.grab_wait_time;
    // auto p1dbreakpush = p1apd.guard_break_pushback;
    // auto p1dcrushtime = p1apd.guard_crush_time;
    // auto p1dguardtime = p1apd.guard_time;
    // auto p1dpushhit = p1apd.hit_pushback;
    auto p1dhstop = p1apd.hitstop;
    // // auto p1dhstopadd = p1apd.hitstop_enemy_addition;
    auto p1dprorate = p1apd.proration;
    auto p1dproratf = p1apd.proration_first;
    auto p1dprorato = p1apd.proration_once;
    auto p1dproratrf = p1apd.proration_rate_first;
    auto p1dproratro = p1apd.proration_rate_once;
    // auto p1dpush = p1apd.pushback;
    auto p1drisc = p1apd.risc;
    // auto p1dstagger = p1apd.stagger_time;
    // auto p1dunburst = p1apd.unburst_time;
    auto p1hatklvl = p1aph.atk_level;
    auto p1hatklvlcl = p1aph.atk_level_clash;
    auto p1hatklvlgr = p1aph.atk_level_guard;
    auto p1hatktyp = p1aph.atk_type;
    auto p1hchipdmg = p1aph.chip_damage;
    auto p1hchpdrate = p1aph.chip_damage_rate;
    auto p1hmg = p1aph.damage;
    // auto p1hfdpush = p1aph.fd_min_pushback;
    // auto p1hgrab = p1aph.grab_wait_time;
    // auto p1hbreakpush = p1aph.guard_break_pushback;
    // auto p1hcrushtime = p1aph.guard_crush_time;
    // auto p1hguardtime = p1aph.guard_time;
    // auto p1hpushhit = p1aph.hit_pushback;
    auto p1hhstop = p1aph.hitstop;
    // auto p1hhstopadd = p1aph.hitstop_enemy_addition;
    auto p1hprorate = p1aph.proration;
    auto p1hproratf = p1aph.proration_first;
    auto p1hprorato = p1aph.proration_once;
    auto p1hproratrf = p1aph.proration_rate_first;
    auto p1hproratro = p1aph.proration_rate_once;
    //auto p1hpush = p1aph.pushback;
    auto p1hrisc = p1aph.risc;
    auto p1hstagger = p1aph.stagger_time;
    auto p1hunburst = p1aph.unburst_time;

    // auto p1enpushx = p1apexn.air_pushback_x; // repeat for p1apexd, p1apexc
    // auto p1enpushy = p1apexn.air_pushback_y;
    //auto p1engrav = p1apexn.atk_gravity;
    auto p1enhitstun = p1apexn.atk_hitstun;
    // auto p1enknocktime = p1apexn.atk_knockdown_time;
    // auto p1enrolltime = p1apexn.atk_roll_time;
    // auto p1enslidetime = p1apexn.atk_slide_time;
    // auto p1ensoftknock = p1apexn.atk_soft_knockdown;
    auto p1enuntech = p1apexn.atk_untech;
    auto p1enwallstick = p1apexn.atk_wallstick_time;
    // auto p1edpushx = p1apexd.air_pushback_x; // repeat for p1apexd, p1apexc
    // auto p1edpushy = p1apexd.air_pushback_y;
    // auto p1edgrav = p1apexd.atk_gravity;
    auto p1edhitstun = p1apexd.atk_hitstun;
    // auto p1edknocktime = p1apexd.atk_knockdown_time;
    // auto p1edrolltime = p1apexd.atk_roll_time;
    // auto p1edslidetime = p1apexd.atk_slide_time;
    // auto p1edsoftknock = p1apexd.atk_soft_knockdown;
    auto p1eduntech = p1apexd.atk_untech;
    auto p1edwallstick = p1apexd.atk_wallstick_time;
    // auto p1ecpushx = p1apexc.air_pushback_x; // repeat for p1apexc, p1apexc
    // auto p1ecpushy = p1apexc.air_pushback_y;
    // auto p1ecgrav = p1apexc.atk_gravity;
    auto p1echitstun = p1apexc.atk_hitstun;
    // auto p1ecknocktime = p1apexc.atk_knockdown_time;
    // auto p1ecrolltime = p1apexc.atk_roll_time;
    // auto p1ecslidetime = p1apexc.atk_slide_time;
    // auto p1ecsoftknock = p1apexc.atk_soft_knockdown;
    auto p1ecuntech = p1apexc.atk_untech;
    auto p1ecwallstick = p1apexc.atk_wallstick_time;

    // i wonder why i do this to myself....
    Output::send<LogLevel::Verbose>(STR("p1afro: {}\n"), p1afro);
    Output::send<LogLevel::Verbose>(STR("p1skillid: {}\n"), p1skillid);
    Output::send<LogLevel::Verbose>(STR("p1skillidreg: {}\n"), p1skillidreg);
    Output::send<LogLevel::Verbose>(STR("p1acttime: {}\n"), p1acttime);
    Output::send<LogLevel::Verbose>(STR("p1air: {}\n"), p1air);
    Output::send<LogLevel::Verbose>(STR("p1atkflg: {}\n"), p1atkflg);
    Output::send<LogLevel::Verbose>(STR("p1bdinv: {}\n"), p1bdinv);
    auto bbslen = findStringLength(p1bbsfile);
    Output::send<LogLevel::Verbose>(STR("p1bbsfile: {}, length: {}\n"), convertToWide2(p1bbsfile), bbslen);
    Output::send<LogLevel::Verbose>(STR("p1blockamnt: {}\n"), p1blockamnt);
    Output::send<LogLevel::Verbose>(STR("p1canact: {}\n"), p1canact);
    Output::send<LogLevel::Verbose>(STR("p1cangatling: {}\n"), p1cangatling);
    Output::send<LogLevel::Verbose>(STR("p1canwhiff: {}\n"), p1canwhiff);
    Output::send<LogLevel::Verbose>(STR("p1cinectr: {}\n"), p1cinectr);
    Output::send<LogLevel::Verbose>(STR("p1ctr: {}\n"), p1ctr);
    Output::send<LogLevel::Verbose>(STR("p1cmnactid: {}\n"), p1cmnactid);
    Output::send<LogLevel::Verbose>(STR("p1enflg: {}\n"), p1enflg);
    Output::send<LogLevel::Verbose>(STR("p1dir: {}\n"), p1dir);
    auto fcmdlen = findStringLength(p1firstcmd);
    Output::send<LogLevel::Verbose>(STR("p1firstcmd: {}, len: {}\n"), convertToWide2(p1firstcmd), fcmdlen);
    auto sprnlen = findStringLength(p1spritename);
    Output::send<LogLevel::Verbose>(STR("p1spritename: {},len: {}\n"), convertToWide2(p1spritename), sprnlen);
    auto bbstlen = findStringLength(p1bbstate);
    Output::send<LogLevel::Verbose>(STR("p1bbstate: {}, len: {}\n"), convertToWide2(p1bbstate), bbstlen);
    auto currlen = findStringLength(p1currmovename);
    Output::send<LogLevel::Verbose>(STR("p1currmovename: {}, len: {}\n"), convertToWide2(p1currmovename), currlen);
    Output::send<LogLevel::Verbose>(STR("p1grav: {}\n"), p1grav);
    Output::send<LogLevel::Verbose>(STR("p1height: {}\n"), p1height);
    Output::send<LogLevel::Verbose>(STR("p1hitstopamnt: {}\n"), p1hitstopamnt);
    Output::send<LogLevel::Verbose>(STR("p1hitstunamnt: {}\n"), p1hitstunamnt);
    Output::send<LogLevel::Verbose>(STR("p1active: {}\n"), p1active);
    Output::send<LogLevel::Verbose>(STR("p1blockstun: {}\n"), p1blockstun);
    Output::send<LogLevel::Verbose>(STR("p1knockdown: {}\n"), p1knockdown);
    Output::send<LogLevel::Verbose>(STR("p1hitstun: {}\n"), p1hitstun);
    Output::send<LogLevel::Verbose>(STR("p1throwinv: {}\n"), p1throwinv);
    Output::send<LogLevel::Verbose>(STR("p1strikeinv: {}\n"), p1strikeinv);
    Output::send<LogLevel::Verbose>(STR("p1hitting: {}\n"), p1hitting);
    auto nextlen = findStringLength(p1nextcmd);
    Output::send<LogLevel::Verbose>(STR("p1nextcmd: {}, len: {}\n"), convertToWide2(p1nextcmd), nextlen);
    Output::send<LogLevel::Verbose>(STR("p1index: {}\n"), p1index);
    Output::send<LogLevel::Verbose>(STR("p1posx: {}\n"), p1posx);
    Output::send<LogLevel::Verbose>(STR("p1posy: {}\n"), p1posy);
    auto baselen = findStringLength(p1scriptbase);
    Output::send<LogLevel::Verbose>(STR("p1scriptbase: {}, len: {}\n"), convertToWide2(p1scriptbase), baselen);
    Output::send<LogLevel::Verbose>(STR("p1slowdown: {}\n"), p1slowdown);
    Output::send<LogLevel::Verbose>(STR("p1thrwrng: {}\n"), p1thrwrng);
    Output::send<LogLevel::Verbose>(STR("p1velx: {}\n"), p1velx);
    Output::send<LogLevel::Verbose>(STR("p1vely: {}\n"), p1vely);
    Output::send<LogLevel::Verbose>(STR("p1wakingup: {}\n"), p1wakingup);
    // Output::send<LogLevel::Verbose>(STR("p1name: {}\n"), p1name);
    // Output::send<LogLevel::Verbose>(STR("p2name: {}\n"), p2name);
    // Output::send<LogLevel::Verbose>(STR("p3name: {}\n"), p3name);
    // Output::send<LogLevel::Verbose>(STR("p4name: {}\n"), p4name);
    // Output::send<LogLevel::Verbose>(STR("p5name: {}\n"), p5name);
    // Output::send<LogLevel::Verbose>(STR("p6name: {}\n"), p6name);
    // Output::send<LogLevel::Verbose>(STR("p7name: {}\n"), p7name);
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
    Output::send<LogLevel::Verbose>(STR("p1datklvl: {}\n"), p1datklvl);
    Output::send<LogLevel::Verbose>(STR("p1datklvlcl: {}\n"), p1datklvlcl);
    Output::send<LogLevel::Verbose>(STR("p1datklvlgr: {}\n"), p1datklvlgr);
    Output::send<LogLevel::Verbose>(STR("p1datktyp: {}\n"), p1datktyp);
    Output::send<LogLevel::Verbose>(STR("p1dchipdmg: {}\n"), p1dchipdmg);
    Output::send<LogLevel::Verbose>(STR("p1dchpdrate: {}\n"), p1dchpdrate);
    Output::send<LogLevel::Verbose>(STR("p1dmg: {}\n"), p1dmg);
    Output::send<LogLevel::Verbose>(STR("p1dfdpush: {}\n"), p1dfdpush);
    Output::send<LogLevel::Verbose>(STR("p1dgrab: {}\n"), p1dgrab);
    Output::send<LogLevel::Verbose>(STR("p1dbreakpush: {}\n"), p1dbreakpush);
    Output::send<LogLevel::Verbose>(STR("p1dcrushtime: {}\n"), p1dcrushtime);
    Output::send<LogLevel::Verbose>(STR("p1dguardtime: {}\n"), p1dguardtime);
    Output::send<LogLevel::Verbose>(STR("p1dpushhit: {}\n"), p1dpushhit);
    Output::send<LogLevel::Verbose>(STR("p1dhstop: {}\n"), p1dhstop);
    Output::send<LogLevel::Verbose>(STR("p1dhstopadd: {}\n"), *p1dhstopadd);
    Output::send<LogLevel::Verbose>(STR("p1dprorate: {}\n"), p1dprorate);
    Output::send<LogLevel::Verbose>(STR("p1dproratf: {}\n"), p1dproratf);
    Output::send<LogLevel::Verbose>(STR("p1dprorato: {}\n"), p1dprorato);
    Output::send<LogLevel::Verbose>(STR("p1dproratrf: {}\n"), p1dproratrf);
    Output::send<LogLevel::Verbose>(STR("p1dproratro: {}\n"), p1dproratro);
    Output::send<LogLevel::Verbose>(STR("p1dpush: {}\n"), p1dpush);
    Output::send<LogLevel::Verbose>(STR("p1drisc: {}\n"), p1drisc);
    Output::send<LogLevel::Verbose>(STR("p1dstagger: {}\n"), p1dstagger);
    Output::send<LogLevel::Verbose>(STR("p1dunburst: {}\n"), p1dunburst);
    Output::send<LogLevel::Verbose>(STR("p1hatklvl: {}\n"), p1hatklvl);
    Output::send<LogLevel::Verbose>(STR("p1hatklvlcl: {}\n"), p1hatklvlcl);
    Output::send<LogLevel::Verbose>(STR("p1hatklvlgr: {}\n"), p1hatklvlgr);
    Output::send<LogLevel::Verbose>(STR("p1hatktyp: {}\n"), p1hatktyp);
    Output::send<LogLevel::Verbose>(STR("p1hchipdmg: {}\n"), p1hchipdmg);
    Output::send<LogLevel::Verbose>(STR("p1hchpdrate: {}\n"), p1hchpdrate);
    Output::send<LogLevel::Verbose>(STR("p1hmg: {}\n"), p1hmg);
    Output::send<LogLevel::Verbose>(STR("p1hfdpush: {}\n"), p1hfdpush);
    Output::send<LogLevel::Verbose>(STR("p1hgrab: {}\n"), p1hgrab);
    Output::send<LogLevel::Verbose>(STR("p1hbreakpush: {}\n"), p1hbreakpush);
    Output::send<LogLevel::Verbose>(STR("p1hcrushtime: {}\n"), p1hcrushtime);
    Output::send<LogLevel::Verbose>(STR("p1hguardtime: {}\n"), p1hguardtime);
    Output::send<LogLevel::Verbose>(STR("p1hpushhit: {}\n"), p1hpushhit);
    Output::send<LogLevel::Verbose>(STR("p1hhstop: {}\n"), p1hhstop);
    Output::send<LogLevel::Verbose>(STR("p1hhstopadd: {}\n"), *p1hhstopadd);
    Output::send<LogLevel::Verbose>(STR("p1hprorate: {}\n"), p1hprorate);
    Output::send<LogLevel::Verbose>(STR("p1hproratf: {}\n"), p1hproratf);
    Output::send<LogLevel::Verbose>(STR("p1hprorato: {}\n"), p1hprorato);
    Output::send<LogLevel::Verbose>(STR("p1hproratrf: {}\n"), p1hproratrf);
    Output::send<LogLevel::Verbose>(STR("p1hproratro: {}\n"), p1hproratro);
    Output::send<LogLevel::Verbose>(STR("p1hpush: {}\n"), p1hpush);
    Output::send<LogLevel::Verbose>(STR("p1hrisc: {}\n"), p1hrisc);
    Output::send<LogLevel::Verbose>(STR("p1hstagger: {}\n"), p1hstagger);
    Output::send<LogLevel::Verbose>(STR("p1hunburst: {}\n"), p1hunburst);
    Output::send<LogLevel::Verbose>(STR("p1enpushx: {}\n"), p1enpushx);
    Output::send<LogLevel::Verbose>(STR("p1enpushy: {}\n"), p1enpushy);
    Output::send<LogLevel::Verbose>(STR("p1engrav: {}\n"), p1engrav);
    Output::send<LogLevel::Verbose>(STR("p1enhitstun: {}\n"), p1enhitstun);
    Output::send<LogLevel::Verbose>(STR("p1enknocktime: {}\n"), p1enknocktime);
    Output::send<LogLevel::Verbose>(STR("p1enrolltime: {}\n"), p1enrolltime);
    Output::send<LogLevel::Verbose>(STR("p1enslidetime: {}\n"), p1enslidetime);
    Output::send<LogLevel::Verbose>(STR("p1ensoftknock: {}\n"), p1ensoftknock);
    Output::send<LogLevel::Verbose>(STR("p1enuntech: {}\n"), p1enuntech);
    Output::send<LogLevel::Verbose>(STR("p1enwallstick: {}\n"), p1enwallstick);
    Output::send<LogLevel::Verbose>(STR("p1edpushx: {}\n"), p1edpushx);
    Output::send<LogLevel::Verbose>(STR("p1edpushy: {}\n"), p1edpushy);
    Output::send<LogLevel::Verbose>(STR("p1edgrav: {}\n"), p1edgrav);
    Output::send<LogLevel::Verbose>(STR("p1edhitstun: {}\n"), p1edhitstun);
    Output::send<LogLevel::Verbose>(STR("p1edknocktime: {}\n"), p1edknocktime);
    Output::send<LogLevel::Verbose>(STR("p1edrolltime: {}\n"), p1edrolltime);
    Output::send<LogLevel::Verbose>(STR("p1edslidetime: {}\n"), p1edslidetime);
    Output::send<LogLevel::Verbose>(STR("p1edsoftknock: {}\n"), p1edsoftknock);
    Output::send<LogLevel::Verbose>(STR("p1eduntech: {}\n"), p1eduntech);
    Output::send<LogLevel::Verbose>(STR("p1edwallstick: {}\n"), p1edwallstick);
    Output::send<LogLevel::Verbose>(STR("p1ecpushx: {}\n"), p1ecpushx);
    Output::send<LogLevel::Verbose>(STR("p1ecpushy: {}\n"), p1ecpushy);
    Output::send<LogLevel::Verbose>(STR("p1ecgrav: {}\n"), p1ecgrav);
    Output::send<LogLevel::Verbose>(STR("p1echitstun: {}\n"), p1echitstun);
    Output::send<LogLevel::Verbose>(STR("p1ecknocktime: {}\n"), p1ecknocktime);
    Output::send<LogLevel::Verbose>(STR("p1ecrolltime: {}\n"), p1ecrolltime);
    Output::send<LogLevel::Verbose>(STR("p1ecslidetime: {}\n"), p1ecslidetime);
    Output::send<LogLevel::Verbose>(STR("p1ecsoftknock: {}\n"), p1ecsoftknock);
    Output::send<LogLevel::Verbose>(STR("p1ecuntech: {}\n"), p1ecuntech);
    Output::send<LogLevel::Verbose>(STR("p1ecwallstick: {}\n"), p1ecwallstick);

    ///player 2 yaaay...
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
    p1 = {};
    p2 = {};
    p1prev = {};
    p2prev = {};
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
 * Alos sends currentFrame
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