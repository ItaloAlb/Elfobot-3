#pragma once
#include "battlelist.h"
#include "map.h"
#include <atomic>

namespace Auto {
        void Targeting(bool& controller);
        void Fishing(bool& controller, Map& map);
        void Attacking(bool& controller);
};