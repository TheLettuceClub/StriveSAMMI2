#pragma once
#include "arcsys.h"
#include <DynamicOutput/DynamicOutput.hpp>
#include <Mod/CppUserModBase.hpp>
// sammi header stuff

void SAMMI_init(); // initalizes sammi object, sends roundStartEvent

void SAMMI_update(AREDGameState_Battle *GameState); // process gamestate, control timers, send events as necessary

void SAMMI_kill(); // sends roundEndEvent, deletes object

enum Character
{
    SOL = 0,
    KY = 1,
    // TODO: fill in other characters
};

struct PlayerState {
    std::wstring steamID;   // unused
    std::wstring steamNick; // unused
    Character character;
    uint16_t health;
    int tensionPulse;
    int tension;
    int burst;
    int risc;
    std::wstring state; // bbscript state name
    std::wstring prevState;
    uint16_t roundWins; // unused
    uint16_t comboCounter;
    int xPosition;
    int yPosition;
};

enum HitType
{
    Normal,
    Counter, // add granularity for levels of counterhit?
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
    void objectCreated(std::wstring objectName, ObjectID creator);                                                                                        // called when stuff like projectiles are created, ignores state update timer
    void roundEnd(Winner winner, RoundEndCause cause);                                                                                               // called when round ends, should stop timers and such until next start
    void comboEnd(uint16_t combo_length, uint16_t damage, ObjectID victim);                                                                          // called when combo end, not sure how the state data works here
    std::wstring getP1State();
    std::wstring getP2State();

private:
    PlayerState p1;
    PlayerState p2;
    PlayerState p1prev;
    PlayerState p2prev;
    uint32_t currentFrame = 0;
};