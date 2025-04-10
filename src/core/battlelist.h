#pragma once
#include "list"
#include "enum.h"
#include "entity.h"

class BattleList {
	public:
		int last_search_index;

		BattleList();

		static std::list<int> GetEntityIdList(Flag flag, int last_search_index = 0);

		static int GetLocalPlayerAddress();

		static int GetCombatSituation();
};
