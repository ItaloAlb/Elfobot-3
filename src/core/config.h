#pragma once
#include <iostream>
#include <vector>

namespace Config {
	struct Pokemon {
		char buff[4] = { 0 };
		char protect[4] = { 0 };
		std::vector<std::string> aoe;
		char cooldown[4] = { 0 };
	};
}