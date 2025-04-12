#pragma once
#include "battlelist.h"

list<int> BattleList::GetEntityIdList(EntityFlag flag) {
	list<int> entity_id_list;
	switch (flag)
	{
	case ALL:
		for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			entity_id_list.push_back(entity.id);
		}
		break;

	case ONLY_WILD_POKEMON:
		for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			if (entity.IsValidWildPokemon())
				entity_id_list.push_back(entity.id);
		}
		break;

	case ONLY_ONE_WILD_POKEMON:
		for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
			Entity entity(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
			if (entity.id == 0)
				break;
			if (entity.IsValidWildPokemon()) {
				entity_id_list.push_back(entity.id);
				break;
			}
		}
		break;
	}
	return entity_id_list;
}

int BattleList::GetLocalPlayerPokemonAddress() {
	for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
		Entity entity = (ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		if (entity.GetId() == 0) {
			break;
		}
		if (entity.IsLocalPlayerPokemon() && entity.GetId() != *POINTER::LOCAL_PLAYER_ID) {
			return (ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		}
	}
	return -1;
}

int BattleList::GetLocalPlayerAddress() {
	for (int i = 0; i < BATTLELIST::MAX_SEARCH; i++) {
		int entity_id = *(int*)(ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		if (entity_id == 0) {
			break;
		}
		if (entity_id == *POINTER::LOCAL_PLAYER_ID) {
			return (ADDRESS::BATTLE_LIST_START_SEARCH + (OFFSET::ENTITY * i));
		}
	}
	return -1;
}

int BattleList::GetCombatSituation() {
	size_t count = GetEntityCount(ONLY_WILD_POKEMON);
	if (count == 0)
		return CombatSituation::NO_ENEMY;
	else if (count == 1)
		return CombatSituation::SINGLE_ENEMY;
	else
		return CombatSituation::MULTIPLE_ENEMIES;
}

int BattleList::GetEntityCount(EntityFlag flag) {
	return GetEntityIdList(flag).size();
}
