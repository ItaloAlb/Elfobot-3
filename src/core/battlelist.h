#pragma once
#include "list"
#include "enum.h"
#include "entity.h"
#include "constant.h"

class BattleList {
	public:

		static std::list<int> GetEntityIdList(EntityFlag flag);

		static int GetLocalPlayerAddress();

		static int GetCombatSituation();

		static int GetEntityCount(EntityFlag flag);

		static int GetLocalPlayerPokemonAddress();
};
