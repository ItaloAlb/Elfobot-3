#pragma once
#include "battlelist.h"
#include "constant.h"

BattleList::BattleList() {
	BattleList::last_search_index = 0;
}

list<int> BattleList::GetEntityIdList(Flag flag, int last_search_index) {
	list<int> entity_id_list;
	switch (flag)
	{
	case ALL:
		for (int i = last_search_index; i < last_search_index + BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			entity_id_list.push_back(entity.id);
		}
	case ONLY_WILD_POKEMON:
		for (int i = last_search_index; i < last_search_index + BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			if (entity.IsValidWildPokemon())
				entity_id_list.push_back(entity.id);
		}
	case ONLY_ONE_WILD_POKEMON:
		for (int i = last_search_index; i < last_search_index + BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			if (entity.IsValidWildPokemon()) {
				entity_id_list.push_back(entity.id);
				break;
			}
		}
	}
	return entity_id_list;
}

int BattleList::GetLocalPlayerAddress() {
	for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
		int entity_id = *(int*)(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		if (entity_id == 0) {
			break;
		}
		if (entity_id == * POINTER::LOCAL_PLAYER_ID) {
			return (ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		}
	}
}
