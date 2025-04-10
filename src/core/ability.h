#pragma once
#include <iostream>
#include <vector>

struct Ability {
    std::string name;
    std::vector<std::string> tags; // e.g., "defensive buff", "aoe", etc.
    int cooldown; // cooldown in seconds or ticks
    float cooldownRemaining;
};
