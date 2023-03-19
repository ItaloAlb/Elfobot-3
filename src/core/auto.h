#pragma once
#include "battlelist.h"
#include "map.h"
#include <atomic>

using namespace std;

namespace Auto {
        void Targeting(std::atomic<bool>& controller);
        void Fishing(std::atomic<bool>& controller, Map& map);
        void Attacking(std::atomic<bool>& controller);
};