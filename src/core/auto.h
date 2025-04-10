#pragma once
#include "battlelist.h"
#include "map.h"
#include "util.h"
#include <functional>
#include <atomic>


namespace Auto {
    extern bool controller_targeting, controller_fishing, controller_attacking, controller_walking, controller_loving, controller_egg_loving, is_wasd_move, top_hunt, controller_connecting;

    extern int aoeCount[6];

    extern char     buff[6][4];
    extern char     protect[6][4];
    extern char     aoe[6][4][4];
    extern char     cooldown[6][4];
    extern int      iCooldown[6];

    extern bool cooldownActive[6];
    extern float cooldownRemaining[6];

    extern int slot[6];

    extern int controller_fishing_rod_container, controller_fishing_rod_id;

    void Targeting(bool& controller);
    void Fishing(bool& controller);
    void Attacking(bool& controller);
    void Loving(bool& controller);
    void Egg_Loving(bool& controller);
    void Connecting(bool& controller);

    void Callback(std::function<void(bool&)> call, bool& controller);
};