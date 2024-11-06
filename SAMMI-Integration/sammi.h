#pragma once
#include "arcsys.h"
#include <DynamicOutput/DynamicOutput.hpp>
#include <Mod/CppUserModBase.hpp>
// sammi header stuff

void SAMMI_init(); // initalizes sammi object, sends roundStartEvent

void SAMMI_update(AREDGameState_Battle *GameState); // process gamestate, control timers, send events as necessary

void SAMMI_kill(); // sends roundEndEvent, deletes object

enum Character // : std::wstring
{
    // alphabetical because id doesn't matter
    ABA,
    ANJ,
    ASK,
    BED,
    BGT,
    BKN,
    CHP,
    COS,
    DZY,
    ELP,
    FAU,
    GIO,
    GLD,
    INO,
    JHN,
    JKO,
    KYK,
    LEO,
    MAY,
    MLL,
    NAG,
    POT,
    RAM,
    SIN,
    SLY,
    SOL,
    TST,
    ZAT
};

struct PlayerState
{
    std::wstring steamID = L"";   // unused
    std::wstring steamNick = L""; // unused
    Character character = SOL;
    uint16_t health = 0;
    int tensionPulse = 0;
    int tension = 0;
    int burst = 0;
    int risc = 0;
    std::wstring state = L""; // bbscript state name
    std::wstring prevState = L"";
    uint16_t roundWins = 0; // unused
    uint16_t comboCounter = 0;
    int xPosition = 0;
    int yPosition = 0;
};

enum HitType
{
    Normal,
    Counter,
    CinematicCounter,
    Unknown,
    Throw
};

enum ObjectID
{
    Player1OID,
    Player2OID,
    Projectile
};

enum Winner
{
    Player1Win,
    Player2Win,
    Draw
};

enum RoundEndCause
{
    Timeout,
    Death
};

class SAMMI
{
public:
    void roundStart();                                                                                                                               // called on round start, should start timers and such
    void stateUpdate(uint32_t roundTimeLimit, uint32_t roundTimeLeft, PlayerState &player1, PlayerState &player2);                                   // called every frame, sends on interval frames
    void hitEvent(HitType hitType, bool wasBlocked, uint8_t attackLevel, uint16_t damage, ObjectID attacker, ObjectID victim, uint16_t comboLength); // called when either player is hit, regardless of interval
    void objectCreated(std::wstring objectName, ObjectID creator);                                                                                   // called when stuff like projectiles are created, ignores state update timer
    void roundEnd(Winner winner, RoundEndCause cause);                                                                                               // called when round ends, should stop timers and such until next start
    void comboEnd(uint16_t combo_length, uint16_t damage, ObjectID victim);                                                                          // called when combo end, not sure how the state data works here
    std::wstring getP1State();
    std::wstring getP2State();

private:
    PlayerState p1 = {};
    PlayerState p2 = {};
    PlayerState p1prev = {};
    PlayerState p2prev = {};
    uint32_t currentFrame = 0;
};