#pragma once
#include "battlelist.h"
#include "map.h"
#include "util.h"
#include <functional>
#include <atomic>


namespace Auto {
    extern bool controller_targeting, controller_fishing, controller_attacking, controller_walking;

    extern int controller_fishing_rod_container, controller_fishing_rod_id;

    void Targeting(bool& controller);
    void Fishing(bool& controller);
    void Attacking(bool& controller);


    void Callback(std::function<void(bool&)> call, bool& controller);
};